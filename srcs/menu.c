/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:22:30 by nboute            #+#    #+#             */
/*   Updated: 2017/04/24 18:04:42 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

void	draw_menu(t_mlx *mlx)
{
	int	i;
	int	j;
	int	bpx;
	int	size;
//	int	range;

	if (!(mlx->menu = (t_img*)malloc(sizeof(t_img))))
		exit (-1);
	mlx->palet = mlx_new_image(mlx->mlx, mlx->moffset, 1000);
	mlx->paletdata = mlx_get_data_addr(mlx->palet, &bpx, &size, &i);
	i = 0;
//	range = ft_map(mlx->colrange, 
	while (i < 50)
	{
		j = 50;
		while (j < mlx->moffset)
		{
			/*
			if (i == 0 || i == 49 || j == 50 || j == 199)
				ft_put_pixel(WHITE, j, i, mlx->menu);*/
//			if (j == mlx->colrange / 10)
			j++;
		}
		i++;
	}
	while (i < 1000)
	{
		j = 0;
		while (j < mlx->moffset)
		{
			*(unsigned*)(mlx->paletdata + j * 4 + i * size) =
				(int)mlx->colors[lroundl(ft_map(i - 50, 950, 0, 1000))];
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->palet, 0, 0);
	mlx_string_put(mlx->mlx, mlx->win, 10, 10, WHITE, "+");
}
