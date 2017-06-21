/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 15:58:52 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 18:21:31 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

int			get_color(int cp)
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

int			ft_gradation(unsigned int col, unsigned int col2, int p)
{
	int		r;
	int		g;
	int		b;

	r = ((col2 >> 16) & 0x000000FF) - ((col >> 16) & 0x000000FF);
	g = ((col2 >> 8) & 0x000000FF) - ((col >> 8) & 0x000000FF);
	b = (col2 & 0x000000FF) - (col & 0x000000FF);
	r = (r * p) / 100;
	g = (g * p) / 100;
	b = (b * p) / 100;
	return (col + r * 65536 + g * 256 + b);
}

int			get_color_grad(int val, int val2, int pre, int perc)
{
	if (pre <= 1)
		return (get_color(val));
	return (ft_gradation(get_color(val / pre), get_color(val2 / pre), perc));
}

int			set_colors_p1(t_mlx *mlx)
{
	int		vals[4];

	if (mlx->colpre < 1)
		mlx->colpre = 1;
	else if (mlx->colpre > 100)
		mlx->colpre = 100;
	vals[0] = ft_lmap(mlx->colstart, 100, 0, mlx->colpre * 10);
	vals[1] = ft_lmap(mlx->colend, 100, 0, mlx->colpre * 10);
	vals[2] = mlx->colpre;
	mlx->changed = 1;
	set_color_values(vals, &mlx->main->nbcols, &mlx->main->colors);
	return (0);
}
