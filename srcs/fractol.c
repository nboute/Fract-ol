/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:48:29 by nboute            #+#    #+#             */
/*   Updated: 2017/05/10 19:39:30 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdio.h>

void		ft_place_pixel(int color, int x, int y, t_img *img)
{
	*(unsigned*)(img->data + x * img->bpx / 8 + y * img->size) = color;
}

int			set_color(int cp)
{
	cp %= 10;
	if (cp == 0)
		return (MAGENTA);
	else if (cp == 1)
		return (RED);
	else if (cp == 2)
		return (ORANGE);
	else if (cp == 3)
		return (YELLOW);
	else if (cp == 4)
		return (GREEN);
	else if (cp == 5)
		return (DARKTURQUOISE);
	else if (cp == 6)
		return (NAVY);
	else if (cp == 7)
		return (BLUE);
	else if (cp == 8)
		return (CYAN);
	else
		return (PURPLE);
}

int	set_colors_p1(t_mlx *mlx)
{
	int		vals[4];

	if (mlx->colpre < 1)
		mlx->colpre = 1;
	else if (mlx->colpre > 100)
		mlx->colpre = 100;
	vals[0] = ft_lmap(mlx->colstart, 100, 0, mlx->colpre * 10);
	vals[1] = ft_lmap(mlx->colend, 100, 0, mlx->colpre * 10);
	vals[2] = mlx->colpre;
	set_color_values(vals, &mlx->main->nbcols, &mlx->main->colors);
	return (0);
}

int			ft_gradation(unsigned int col, unsigned int col2, int p)
{
	int	r;
	int	g;
	int	b;

	r = ((col2 >> 16) & 0x000000FF) - ((col >> 16) & 0x000000FF);
	g = ((col2 >> 8) & 0x000000FF) - ((col >> 8) & 0x000000FF);
	b = (col2 & 0x000000FF) - (col & 0x000000FF);
	r = (r * p) / 100;
	g = (g * p) / 100;
	b = (b * p) / 100;
	return (col + r * 65536 + g * 256 + b);
}

int			get_color(int val, int val2, int pre, int perc)
{
	if (pre <= 1)
		return (set_color(val));
	return (ft_gradation(set_color(val / pre),
				set_color(val2 / pre), perc));
}

void	mandelbrot(int i, int j, t_mlx *mlx)
{
	double	vals[5];
	int		iter;
	//	int		color;

	vals[0] = ft_dmap(i, mlx->width, mlx->xmin, mlx->xmax);
	vals[1] = ft_dmap(j, mlx->height, mlx->ymin, mlx->ymax);
	vals[2] = 0;
	vals[3] = 0;
	iter = 0;
	while (vals[2] * vals[2] + vals[3] * vals[3] < 4 && iter < mlx->maxiter)
	{
		vals[4] = vals[2] * vals[2] - vals[3] * vals[3] + vals[0];
		vals[3] = 2 * vals[2] * vals[3] + vals[1];
		vals[2] = vals[4];
		iter++;
	}
	ft_place_pixel(mlx->main->colors[(iter + mlx->index) % mlx->main->nbcols],
			i, j, mlx->main);
}

void	burning_ship(int i, int j, t_mlx *mlx)
{
	double	vals[5];
	int		iter;
	//	int		color;
	vals[0] = ft_dmap(i, mlx->width, mlx->xmin, mlx->xmax);
	vals[1] = ft_dmap(j, mlx->height, mlx->ymin, mlx->ymax);
	vals[2] = 0;
	vals[3] = 0;
	iter = 0;
	while (vals[2] * vals[2] + vals[3] * vals[3] < 4 && iter < mlx->maxiter)
	{
		if (vals[2] < 0)
			vals[2] *= -1;
		if (vals[3] < 0)
			vals[3] *= -1;
		vals[4] = vals[2] * vals[2] - vals[3] * vals[3] + vals[0];
		vals[3] = 2 * vals[2] * vals[3] + vals[1];
		vals[2] = vals[4];
		iter++;
	}
	//	color = ((100 / mlx->colpre) * (iter % mlx->nbcols) +
	//			mlx->colstart) % MAX_COLS;
	ft_place_pixel(mlx->main->colors[(iter + mlx->index) % mlx->main->nbcols], i, j, mlx->main);
}
int	draw_mandelbrot(t_mlx *mlx)
{
	int	i = 0;
	int		j;

	while (i < mlx->width)
	{
		j = 0;
		while (j < mlx->height)
			//			burning_ship(i, j++, mlx);
			mandelbrot(i, j++, mlx);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, mlx->moffset, 0);
	return (0);
}
/*
 ** vals: 0 = color start 1 = color end 2 = color precision (shading, 1 to 100)
 ** (on 0 to 1000 scale for start & end, referring to preselected color values)
 ** 3 = value for last shading loop
 */
int		*set_color_values_p2(int vals[4], int *nbcols, int **colors)
{
	int	i;
	int	j;
	int	tmp[2];
	double perc;

	perc = ft_dmap(vals[0] % vals[2], vals[2], 0, 100);
	i = 0;
	while (i < *nbcols)
	{
		tmp[0] = ((vals[0] + i) - (vals[0] + i) % vals[2]) % (vals[2] * 10 + 1);
		tmp[1] = (tmp[0] + vals[2]) % (vals[2] * 10);
		if ((vals[0] + i) % vals[2] == 0)
			perc = 0;
		if (perc > 100)
			perc = 100;
		(*colors)[i] = get_color(tmp[0], tmp[1], vals[2], lround(perc));
		perc = perc + ft_dmap(1, vals[2], 0, 100);
		i++;
	}
	*nbcols += vals[3];
	j = 0;
	tmp[0] = get_color(vals[0] - (vals[0] % vals[2]),
			(vals[0] + vals[2]) % ((vals[2] * 9) + 1),
			vals[2], ft_lmap(vals[0] % vals[2], vals[2], 0, 100));
	while (j < vals[3])
	{
		perc = ft_dmap(j, vals[3], 0, 100);
		if (perc > 100)
			perc = 100;
		(*colors)[i + j] = ft_gradation((*colors)[i - 1], tmp[0], lround(perc));
		j++;
	}
	return (*colors);
}

int		*set_color_values(int vals[4], int *nbcols, int **colors)
{
	*nbcols = labs(vals[1] - vals[0]);
	if (vals[1] < vals[0])
		*nbcols = vals[2] * 10 - *nbcols;
	vals[3] = 0;
	if (*nbcols <= vals[2])
		vals[3] = *nbcols;
	else if (*nbcols >= vals[2] * 9 && *nbcols < vals[2] * 10)
		vals[3] = vals[2] * 10 - *nbcols;
	else if (*nbcols != vals[2] * 10)
		vals[3] = vals[2];
	if (*colors)
		free(*colors);
	if (!(*colors = (int*)malloc(sizeof(int) * (*nbcols + vals[3]))))
		return (0);
	return (set_color_values_p2(vals, nbcols, colors));
}
/*
   int		*set_color_values(int vals[3], int *nbcols, int **colors)
   {
   int	i;
   int	j;
   int	k;

   i = 0;
 *nbcols = labs(vals[1] - vals[0]);
 k = 0;
 if (*nbcols <= vals[2])
 k = *nbcols;
 else if (*nbcols > vals[2] * 10 - vals[2] && *nbcols < vals[2] * 10)
 k = vals[2] * 10 - vals[2];
 else if (*nbcols != vals[2] * 10)
 k = vals[2];
 if (*colors)
 free(*colors);
 if (!(*colors = (int*)malloc(sizeof(int) * (*nbcols + k))))
 return (0);
 int	val1;
 int val2;
 double	perc;
 perc = ft_dmap(vals[0] % vals[2], vals[2], 0, 100);
 while (i < *nbcols)
 {
 val1 = ((vals[0] + i) - (vals[0] + i) % vals[2]) % (vals[2] * 10);
 val2 = (val1 + vals[2]) % (vals[2] * 10);
 perc = (perc + ft_dmap(1, vals[2], 0, 100));
//		perc = ft_map(i % mlx->colpre, mlx->colpre, 0, 100);
(*colors)[i] = get_color(val1, val2, vals[2], perc);
printf("%X\n", (*colors)[i]);
//		mlx->colors[i] = get_color((mlx->colstart + 5 * (i / 50)) %
//				(mlx->colpre * 10), (mlx->colstart + 50 * ((i % 50 + 1)))
//				% (mlx->colpre * 10), mlx->colpre, (i % mlx->colpre));
perc -= (perc >= 100) ? 100 : 0;
i++;
}
 *nbcols += k;
 j = 0;
 val1 = get_color(vals[0] - (vals[0] % vals[2]),
 (vals[0] + vals[2]) % (vals[2] * 10),
 vals[2], ft_lmap(vals[0] % vals[2], vals[2], 0, 100));
 while (j < k)
 {
 perc = ft_dmap(j, k, 0, 100);
 (*colors)[i + j] = ft_gradation((*colors)[i - 1], val1, perc);
 printf("%X|%X\n", val1, (*colors)[i + j]);
 j++;
 }
 return (*colors);
 }
 */

int		menu_action(int x, int y, t_mlx *mlx, int button)
{
	if (y >= 60)
	{
		if (button == 1)
			mlx->colstart = ft_lmap(y - 60, 940, 0, 100);
		if (button == 2)
			mlx->colend = ft_lmap(y - 60, 940, 0, 100);
		if (mlx->colstart == mlx->colend)
			mlx->colend = (mlx->colstart + 1) % 100;
		set_colors_p1(mlx);
	}
	if (x >= 0 && x < 30 && y >= 0 && y < 30)
	{
		if (mlx->mval == 1)
			if (mlx->colpre < 100)
				mlx->colpre++;
		if (mlx->mval == 0)
			if (mlx->maxiter < 1000)
				mlx->maxiter++;
	}
	else if (x >= 0 && x < 30 && y >= 30 && y < 60)
	{
		if (mlx->mval == 1)
			if (mlx->colpre > 1)
				mlx->colpre--;
		if (mlx->mval == 0)
			if (mlx->maxiter > 10)
				mlx->maxiter--;
	}
	else if (x >= 30 && y >= 0 && y < 30)
		mlx->mval = 0;
	else if (x >= 30 && y >= 30 && y < 60)
		mlx->mval = 1;
	if (mlx->mval == 1)
		set_colors_p1(mlx);
	printf("%d\n", mlx->mval);
	return (0);
}

int			mouse_pressed(int button, int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = param;
	if ((button == 1 || button == 2) && x < mlx->moffset)
	{
		menu_action(x, y, mlx, button);
	}
	x -= mlx->moffset;
	if (x > 0 && button == 4 && mlx->ratio < ft_power(2, 22))
	{
		mlx->ratio *= 2;
		mlx->xmin = ft_dmap(x, 1000, mlx->xmin, mlx->xmax) - (2.5 / (2 * mlx->ratio));
		mlx->xmax = mlx->xmin + ((double)2.5 / (double)mlx->ratio);
		mlx->ymin = ft_dmap(y, 1000, mlx->ymin, mlx->ymax) - (2.5 / (2 * mlx->ratio));
		mlx->ymax = mlx->ymin + ((double)2.5 / (double)mlx->ratio);
		printf("%lf|%lf\n", mlx->ymin, mlx->ymax);
	}
	if (x > 0 && button == 5 && mlx->ratio > 1)
	{
		mlx->ratio /= 2;
		mlx->xmin = ft_dmap(x, 1000, mlx->xmin, mlx->xmax) - (2.5 / (2 * mlx->ratio));
		mlx->xmax = mlx->xmin + ((double)2.5 / (double)mlx->ratio);
		mlx->ymin = ft_dmap(y, 1000, mlx->ymin, mlx->ymax) - (2.5 / (2 * mlx->ratio));
		mlx->ymax = mlx->ymin + ((double)2.5 / (double)mlx->ratio);
	}
	/*	else if (button == 1 && x < 0 && y > 49)
		{
		if (y < 49)
		y = 49;
		mlx->colset = y;
		}
		*/	return (0);
}

void	ft_move_cursor(t_mlx *mlx, double x, double y)
{
	mlx->xmin += (x / (2 * mlx->ratio));
	mlx->xmax += (x / (2 * mlx->ratio));
	mlx->ymin += (y / (2 * mlx->ratio));
	mlx->ymax += (y / (2 * mlx->ratio));
}

int		key_pressed(int key, void *ptr)
{
	t_mlx *mlx;

	mlx = (t_mlx*)ptr;
	if (key >= 82 && key <= 92)
	{
		if (mlx->mval == 0)
			mlx->maxiter = (mlx->maxiter * 10 + key - 82) % 100;
		if (mlx->mval == 1)
		{
			mlx->colpre = (mlx->colpre * 10 + key - 82) % 101;
			set_colors_p1(mlx);
		}
	}
	if (key == 69)
	{
		mlx->maxiter += 10;
		printf("%d\n", mlx->maxiter);
	}
	if (key == 78)
	{
		if (mlx->maxiter > 10)
			mlx->maxiter -= 10;
	}
	else if (key == 126)
		ft_move_cursor(mlx, 0, -1);
	else if (key == 125)
		ft_move_cursor(mlx, 0, 1);
	else if (key == 124)
		ft_move_cursor(mlx, 1, 0);
	else if (key == 123)
		ft_move_cursor(mlx, -1, 0);
	else if (key == 49)
		mlx->autoiter = (mlx->autoiter + 1) % 2;
	else
		return (0);
	return (1);
}

int		ft_loop(void *pass)
{
	t_mlx *mlx;

	mlx = (t_mlx*)pass;
	mlx->maxiter += mlx->autoiter;
	mlx->index += 1;
	draw_mandelbrot(mlx);
	draw_menu(mlx);
	/*	mlx->itratio += 1;
		if (!(mlx->itratio % 100))
		{
		mlx->maxiter++;
		draw_mandelbrot(mlx);
		}
		*/	return (0);
}



int		main(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (-1);
	if (!(mlx->main = (t_img*)malloc(sizeof(t_img))))
		return (-1);
	mlx->mlx = mlx_init();
	mlx->main->colors = NULL;
	mlx->colstart = 0;
	mlx->index = 0;
	mlx->colend = 100;
	mlx->colpre = 20;
	mlx->menu = NULL;
	mlx->main->nbcols = 0;
	mlx->moffset = 200;
	set_colors_p1(mlx);
	mlx->win = mlx_new_window(mlx->mlx, 1000 + mlx->moffset, 1000, "Fract'ol");
	mlx->img = NULL;
	mlx->xmin = -2;
	mlx->xmax = 0.5;
	mlx->ymin = -1.25;
	mlx->ymax = 1.25;
	mlx->ratio = 1;
	mlx->height = 1000;
	mlx->width = 1000;
	mlx->maxiter = 1;
	mlx->autoiter = 0;
	mlx->img = mlx_new_image(mlx->mlx, mlx->height, mlx->width);
	mlx->main->data = mlx_get_data_addr(mlx->img, &mlx->main->bpx,
			&mlx->main->size, &mlx->main->end);
	draw_menu(mlx);
	draw_mandelbrot(mlx);
	mlx_mouse_hook(mlx->win, &mouse_pressed, mlx);
	mlx_key_hook(mlx->win, &key_pressed, mlx);
	mlx_loop_hook(mlx->mlx, &ft_loop, (void*)mlx);
	draw_mandelbrot(mlx);
	mlx_loop(mlx->mlx);
}
