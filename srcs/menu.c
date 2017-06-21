/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:22:30 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 18:32:51 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdio.h>

void	get_palet(int **colors, int *nbcols)
{
	int	vals[4];

	vals[0] = 0;
	vals[1] = 1000;
	vals[2] = 100;
	set_color_values(vals, nbcols, colors);
}

void	menu_action_p2(int x, int y, t_mlx *mlx)
{
	if (x >= 0 && x < 30 && y >= 30 && y < 60)
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
}

void	menu_action(int x, int y, t_mlx *mlx, int button)
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
	else
		menu_action_p2(x, y, mlx);
	if (mlx->mval == 1)
		set_colors_p1(mlx);
}

void	draw_menu_p2(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->menu->img, 0, 0);
	if (mlx->mval == 0)
	{
		mlx_string_put(mlx->mlx, mlx->win, 75, 5, 0x00FFFFFF, "ITER MAX");
		mlx_string_put(mlx->mlx, mlx->win, 110 - (ft_nbdigits(mlx->maxiter) * 5)
				/ 2, 35, WHITE, ft_itoa(mlx->maxiter));
	}
	else
	{
		mlx_string_put(mlx->mlx, mlx->win, 75, 35, 0x00FFFFFF, "DEGRADES");
		mlx_string_put(mlx->mlx, mlx->win, 110 - (ft_nbdigits(mlx->maxiter) * 5)
				/ 2, 5, WHITE, ft_itoa(mlx->colpre));
	}
}

void	draw_menu(t_mlx *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 60)
	{
		j = 0;
		while (j < mlx->moffset)
		{
			if ((i == 0 || (i == 30) || i == 59 || j == 0 || j == 30 ||
					j == mlx->moffset - 1) || ((i == 14 && j > 4 && j < 26)
						|| (j == 14 && i > 4 && i < 26) ||
						(i == 44 && j >= 7 && j <= 23)))
				ft_place_pixel(CYAN, j, i, mlx->menu);
			else
				ft_place_pixel(BLACK, j, i, mlx->menu);
			if (mlx->mval == 0 && (((i == 0 || i == 29) && j > 30) ||
						((j == 30 || j == mlx->moffset - 1) && i < 30)))
				ft_place_pixel(RED, j, i, mlx->menu);
			else if (mlx->mval == 1 && (((i == 30 || i == 59) && j > 30) ||
						((j == 30 || j == mlx->moffset - 1) && i >= 30)))
				ft_place_pixel(RED, j, i, mlx->menu);
			j++;
		}
	}
}
