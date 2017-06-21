/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 16:04:47 by nboute            #+#    #+#             */
/*   Updated: 2017/06/19 16:14:04 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void		julia(int x, int y, t_mlx *mlx)
{
	double	vals[3];
	int		i;

	vals[1] = 1.5 * (x - mlx->width / 2) / (0.5 * mlx->width * mlx->zoom)
		+ mlx->padx;
	vals[2] = (y - mlx->height / 2) / (0.5 * mlx->height * mlx->zoom)
		+ mlx->pady;
	i = 0;
	while (i < mlx->maxiter)
	{
		vals[0] = vals[1];
		vals[1] = vals[0] * vals[0] - vals[2] * vals[2] + mlx->xmin;
		vals[2] = 2 * vals[0] * vals[2] + mlx->ymin;
		if ((vals[1] * vals[1] + vals[2] * vals[2]) > 4)
			break ;
		i++;
	}
	mlx->pixels[y][x] = mlx->main->colors[(i + mlx->index) % mlx->main->nbcols];
	ft_place_pixel(mlx->pixels[y][x], x, y, mlx->main);
}

void		mandelbrot(int x, int y, t_mlx *mlx)
{
	double	vals[5];
	int		i;

	vals[0] = ft_dmap(x, mlx->width, mlx->xmin, mlx->xmax);
	vals[1] = ft_dmap(y, mlx->height, mlx->ymin, mlx->ymax);
	vals[2] = 0;
	vals[3] = 0;
	i = 0;
	while (vals[2] * vals[2] + vals[3] * vals[3] < 4 && i < mlx->maxiter)
	{
		vals[4] = vals[2] * vals[2] - vals[3] * vals[3] + vals[0];
		vals[3] = 2 * vals[2] * vals[3] + vals[1];
		vals[2] = vals[4];
		i++;
	}
	mlx->pixels[y][x] = mlx->main->colors[(i + mlx->index) % mlx->main->nbcols];
	ft_place_pixel(mlx->pixels[y][x], x, y, mlx->main);
}

void		burning_ship(int x, int y, t_mlx *mlx)
{
	double	vals[5];
	int		i;

	vals[0] = ft_dmap(x, mlx->width, mlx->xmin, mlx->xmax);
	vals[1] = ft_dmap(y, mlx->height, mlx->ymin, mlx->ymax);
	vals[2] = 0;
	vals[3] = 0;
	i = 0;
	while (vals[2] * vals[2] + vals[3] * vals[3] < 4 && i < mlx->maxiter)
	{
		if (vals[2] < 0)
			vals[2] *= -1;
		if (vals[3] < 0)
			vals[3] *= -1;
		vals[4] = vals[2] * vals[2] - vals[3] * vals[3] + vals[0];
		vals[3] = 2 * vals[2] * vals[3] + vals[1];
		vals[2] = vals[4];
		i++;
	}
	mlx->pixels[y][x] = mlx->main->colors[(i + mlx->index) % mlx->main->nbcols];
	ft_place_pixel(mlx->pixels[y][x], x, y, mlx->main);
}
