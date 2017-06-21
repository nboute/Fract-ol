/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:54:05 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 17:10:18 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			mouse_pressed_p2(int button, int x, int y, t_mlx *mlx)
{
	mlx->zoom *= button == 4 ? 2 : 0.5;
	if (mlx->fractal != 2)
	{
		mlx->xmin = ft_dmap(x, 1000, mlx->xmin, mlx->xmax) -
			(2.5 / (2 * mlx->zoom));
		mlx->xmax = mlx->xmin + ((double)2.5 / (double)mlx->zoom);
		mlx->ymin = ft_dmap(y, 1000, mlx->ymin, mlx->ymax) -
			(2.5 / (2 * mlx->zoom));
		mlx->ymax = mlx->ymin + ((double)2.5 / (double)mlx->zoom);
	}
	else
	{
		mlx->vary = (mlx->zoom == 1) ? 1 : 0;
		mlx->padx += button == 4 ? ft_dmap(x, 1000, -2, 2) /
			(mlx->zoom) : -mlx->padx / mlx->zoom;
		mlx->pady += button == 4 ? ft_dmap(y, 1000, -2, 2) /
			(mlx->zoom) : -mlx->pady / mlx->zoom;
	}
	mlx->changed = 1;
	return (1);
}

int			mouse_pressed(int button, int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if ((button == 1 || button == 2) && x < mlx->moffset)
	{
		menu_action(x, y, mlx, button);
	}
	x -= mlx->moffset;
	if (x > 0 && ((button == 4 && mlx->zoom < ft_power(2, 22)) ||
				(button == 5 && mlx->zoom > 1)))
		mouse_pressed_p2(button, x, y, mlx);
	else
		return (0);
	return (1);
}

int			mouse_hover(int x, int y, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx*)param;
	x -= 200;
	if (x <= 0 || x >= mlx->width || y < 0 || y >= 1000 || !mlx->vary ||
			mlx->fractal != 2)
		return (0);
	mlx->xmin = ft_dmap(x, 1000, 0, -1.25);
	mlx->ymin = ft_dmap(y, 1000, 0, 1.25);
	mlx->changed = 1;
	return (1);
}

void		ft_move_cursor(t_mlx *mlx, double x, double y)
{
	if (mlx->fractal != 2)
	{
		mlx->xmin += (x / (2 * mlx->zoom));
		mlx->xmax += (x / (2 * mlx->zoom));
		mlx->ymin += (y / (2 * mlx->zoom));
		mlx->ymax += (y / (2 * mlx->zoom));
	}
	else
	{
		mlx->padx += x / (2 * mlx->zoom);
		mlx->pady += y / (2 * mlx->zoom);
	}
	mlx->changed = 1;
}
