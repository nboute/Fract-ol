/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:48:29 by nboute            #+#    #+#             */
/*   Updated: 2017/04/26 18:06:01 by nboute           ###   ########.fr       */
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
	if (cp == 0)
		return (MAGENTA);
	else if (cp == 1)
		return (RED);
	else if (cp == 2)
		return (ORANGE);
	else if (cp == 3)
		return (YELLOW);
	else if (cp == 4)
		return (LIME);
	else if (cp == 5)
		return (GREEN);
	else if (cp == 6)
		return (CYAN);
	else if (cp == 7)
		return (BLUE);
	else if (cp == 8)
		return (NAVY);
	else
		return (PURPLE);
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
	return (ft_gradation(set_color((val / pre) % 10),
				set_color(((val2 / pre)) % 10), perc));
}

void	mandelbrot(int i, int j, t_mlx *mlx)
{
	double	vals[5];
	int		iter;
//	int		color;

	vals[0] = ft_map(i, mlx->width, mlx->xmin, mlx->xmax);
	vals[1] = ft_map(j, mlx->height, mlx->ymin, mlx->ymax);
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
//	color = ((100 / mlx->colpre) * (iter % mlx->nbcols) +
//			mlx->colstart) % MAX_COLS;
	ft_place_pixel(mlx->colors[iter % mlx->nbcols], i, j, mlx->main);
}

int	draw_mandelbrot(t_mlx *mlx)
{
	int	i = 0;
	int		j;

	while (i < mlx->width)
	{
		j = 0;
		while (j < mlx->height)
			mandelbrot(i, j++, mlx);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, mlx->moffset, 0);
	return (0);
}

int		*set_color_values(t_mlx *mlx)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	mlx->nbcols = ABS(mlx->colend - mlx->colstart);
	if (mlx->nbcols > 0 && mlx->nbcols < mlx->colpre)
		k = mlx->nbcols;
	else if (mlx->nbcols > mlx->colpre * 9 && mlx->nbcols < mlx->colpre * 10)
		k = mlx->colpre * 10 - mlx->nbcols;
	else if (mlx->nbcols >= mlx->colpre && mlx->nbcols <=  - mlx->colpre)
		k = mlx->colpre;
	if (mlx->colors)
		free(mlx->colors);
	if (!(mlx->colors = (int*)malloc(sizeof(int) * (mlx->nbcols + k))))
		return (0);
	printf("%d\n", k);
	int	val1;
	int val2;
	int	perc;
	perc = mlx->colstart % mlx->colpre;
	while (i < mlx->nbcols)
	{
		val1 = (mlx->colstart + mlx->colpre * (i / mlx->colpre) - mlx->colstart % mlx->colpre) % (mlx->colpre * 10);
		val2 = (val1 + mlx->colpre) % (mlx->colpre * 10);
		perc = (perc + ft_imap(i % mlx->colpre, mlx->colpre, 0, 100)) % 100;
//		perc = ft_map(i % mlx->colpre, mlx->colpre, 0, 100);
		mlx->colors[i] = get_color(val1, val2, mlx->colpre, perc);
//		mlx->colors[i] = get_color((mlx->colstart + 5 * (i / 50)) %
//				(mlx->colpre * 10), (mlx->colstart + 50 * ((i % 50 + 1)))
//				% (mlx->colpre * 10), mlx->colpre, (i % mlx->colpre));
		printf("|val1:%d|val2:%d|pre:%d|perc:%d|col1:%d|%d\n", val1, val2, mlx->colpre, perc, mlx->colstart, i);
		getchar();
		i++;
	}
	mlx->nbcols += k;
	i = 0;
	j = 0;
	while (j < k)
	{
		mlx->colors[i + j] = get_color((mlx->colstart + i), mlx->colend,
				mlx->colpre, ft_map(j, k, 0, 100));
		j++;
	}
	return (mlx->colors);
}

int			mouse_pressed(int button, int x, int y, void *param)
{
	t_mlx *mlx;

	mlx = param;
	x -= mlx->moffset;
	printf("%d|%d|%d\n", button, x, y);
	if (x > 0 && button == 2 && mlx->ratio < ft_power(2, 22))
	{
		mlx->ratio *= 2;
		double	vals[4];
		vals[0] = ft_map(x, 1000, mlx->xmin, mlx->xmax) - (2.5 / (2 * mlx->ratio));
		vals[1] = vals[0] + ((double)2.5 / (double)mlx->ratio);
		vals[2] = ft_map(y, 1000, mlx->ymin, mlx->ymax) - (2.5 / (2 * mlx->ratio));
		vals[3] = vals[2] + ((double)2.5 / (double)mlx->ratio);
		mlx->xmin = vals[0];
		mlx->xmax = vals[1];
		mlx->ymin = vals[2];
		mlx->ymax = vals[3];
		printf("|%f|%f|\n|%f|%f|\n", vals[0], vals[1], vals[2], vals[3]);
		draw_mandelbrot(mlx);
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

int		key_pressed(int key, void *mlx)
{
	if (key == 69)
	{
		((t_mlx*)mlx)->maxiter += 10;
		printf("%d\n", ((t_mlx*)mlx)->maxiter);
	}
	else if (key == 126)
		ft_move_cursor(mlx, 0, -1);
	else if (key == 125)
		ft_move_cursor(mlx, 0, 1);
	else if (key == 124)
		ft_move_cursor(mlx, 1, 0);
	else if (key == 123)
		ft_move_cursor(mlx, -1, 0);
	else
		return (0);
		draw_mandelbrot(mlx);
	return (1);
}

int		ft_loop(void *pass)
{
	t_mlx *mlx;

	mlx = (t_mlx*)pass;
	if (mlx->maxiter >= 2000)

		return (0);
	mlx->maxiter++;
		draw_mandelbrot(mlx);
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
	t_mlx *mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (-1);
	if (!(mlx->main = (t_img*)malloc(sizeof(t_img))))
		return (-1);
	mlx->mlx = mlx_init();
	mlx->colors = NULL;
	mlx->colstart = 170;
	mlx->colend = 643;
	mlx->colpre = 25;
	mlx->nbcols = 0;
	set_color_values(mlx);
	mlx->moffset = 200;
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
	mlx->img = mlx_new_image(mlx->mlx, mlx->height, mlx->width);
	mlx->main->data = mlx_get_data_addr(mlx->img, &mlx->main->bpx,
			&mlx->main->size, &mlx->main->end);
//	draw_menu(mlx);
	draw_mandelbrot(mlx);
	mlx_mouse_hook(mlx->win, &mouse_pressed, mlx);
	mlx_key_hook(mlx->win, &key_pressed, mlx);
	mlx_loop_hook(mlx->mlx, &ft_loop, (void*)mlx);
	mlx_loop(mlx->mlx);
}
