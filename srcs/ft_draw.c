/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 16:06:36 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 18:31:01 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdio.h>

void			ft_place_pixel(int color, int x, int y, t_img *img)
{
	*(unsigned*)(img->data + x * img->bpx / 8 + y * img->size) = color;
}

void			ft_reset(t_mlx *mlx)
{
	if (!mlx->fractal || mlx->fractal == 1)
	{
		mlx->xmin = -2;
		mlx->xmax = 0.5;
		mlx->ymin = -1.25;
		mlx->ymax = 1.25;
	}
	if (mlx->fractal == 1)
	{
		mlx->xmax = 1.25;
		mlx->ymin = -2.25;
	}
	else if (mlx->fractal == 2)
	{
		mlx->xmin = -0.7;
		mlx->ymin = 0.27015;
		mlx->padx = 0;
		mlx->pady = 0;
	}
	mlx->vary = 1;
	mlx->zoom = 1;
	mlx->indexi = 0;
	mlx->index = 0;
	mlx->changed = 1;
}

void			*draw_fractal(void *thread)
{
	int			x;
	int			y;
	t_thread	*data;

	data = (t_thread*)thread;
	y = data->part * 125;
	while (y < ((data->part + 1) * 125))
	{
		x = 0;
		while (x < data->mlx->width)
		{
			if (!data->mlx->changed)
				ft_place_pixel(data->mlx->pixels[y][x], x, y, data->mlx->main);
			else if (data->mlx->fractal == 0)
				mandelbrot(y, x, data->mlx);
			else if (data->mlx->fractal == 1)
				burning_ship(y, x, data->mlx);
			else if (data->mlx->fractal == 2)
				julia(y, x, data->mlx);
			x++;
		}
		y++;
	}
	return (0);
}

void			ft_threads(t_mlx *mlx)
{
	t_thread	data[8];
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	while (i < 8 && !ret)
	{
		data[i].part = i;
		data[i].mlx = mlx;
		ret = pthread_create(&data[i].thread, NULL, draw_fractal,
				(void*)(&data[i]));
		i++;
	}
	if (ret)
		exit(-1);
	i = 0;
	while (i < 8)
		pthread_join(data[i++].thread, NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->main->img, mlx->moffset,
			0);
}

int				ft_loop(void *pass)
{
	t_mlx		*mlx;

	mlx = (t_mlx*)pass;
	mlx->maxiter += mlx->autoiter;
	mlx->index += mlx->indexi;
	if (mlx->changed || mlx->autoiter || mlx->indexi)
		ft_threads(mlx);
	if (!mlx->indexi && !mlx->autoiter)
		mlx->changed = 0;
	else
		mlx->changed = 1;
	if (!mlx->menu)
		setup_menu(mlx);
	draw_palet(mlx->menu, mlx->moffset, mlx->colstart, mlx->colend);
	draw_menu(mlx);
	return (0);
}
