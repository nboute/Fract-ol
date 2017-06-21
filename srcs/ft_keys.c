/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:57:13 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 18:18:43 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int		key_pressed_p2(int key, t_mlx *mlx)
{
	if (key == 126)
		ft_move_cursor(mlx, 0, -1);
	else if (key == 125)
		ft_move_cursor(mlx, 0, 1);
	else if (key == 124)
		ft_move_cursor(mlx, 1, 0);
	else if (key == 123)
		ft_move_cursor(mlx, -1, 0);
	else if (key == 49)
		mlx->autoiter = (mlx->autoiter + 1) % 2;
	else if (key == 15)
		ft_reset(mlx);
	else if (key == 35)
		mlx->vary = mlx->vary == 1 ? 0 : 1;
	else if (key == 47 || key == 43)
	{
		mlx->fractal += (key == 47) ? 1 : -1;
		mlx->fractal %= 3;
		ft_reset(mlx);
	}
	else if (key == 34)
		mlx->indexi = (mlx->indexi + 1) % 2;
	else if (key == 53)
		exit(0);
	return (0);
}

int		key_pressed(int key, void *ptr)
{
	t_mlx *mlx;

	mlx = (t_mlx*)ptr;
	if ((key >= 82 && key <= 92 && key != 90) || key == 69 ||
			(key == 78 && mlx->maxiter > 10) || (key >= 123 && key <= 126))
		mlx->changed = 1;
	if (key >= 82 && key <= 92 && key != 90)
	{
		if (key > 90)
			key--;
		if (mlx->mval == 0)
			mlx->maxiter = (mlx->maxiter * 10 + key - 82) % 1000;
		if (mlx->mval == 1)
			mlx->colpre = (mlx->colpre * 10 + key - 82) % 100;
		if (mlx->mval == 1)
			set_colors_p1(mlx);
	}
	else if (key == 69)
		mlx->maxiter += 10;
	else if (key == 78 && mlx->maxiter > 10)
		mlx->maxiter -= 10;
	else
		return (key_pressed_p2(key, mlx));
	return (1);
}
