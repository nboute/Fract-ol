/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 17:48:29 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 18:23:48 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"
#include <stdio.h>

/*
** vals
** 0 const real
** 1 const ima
** else valeurs tmp
** pairs = nb reel, impair = imaginaire
*/

void	setup_menu(t_mlx *mlx)
{
	mlx->mval = 0;
	if (!(mlx->menu = (t_img*)malloc(sizeof(t_img))))
		exit(-1);
	mlx->menu->img = mlx_new_image(mlx->mlx, mlx->moffset, 1000);
	mlx->menu->data = mlx_get_data_addr(mlx->menu->img, &mlx->menu->bpx,
			&mlx->menu->size, &mlx->menu->end);
	mlx->menu->colors = NULL;
	get_palet(&mlx->menu->colors, &mlx->menu->nbcols);
}

void	ft_set_fractal(t_mlx *mlx, char *fractal)
{
	if (!ft_strcmp(fractal, "mandelbrot"))
		mlx->fractal = 0;
	else if (!ft_strcmp(fractal, "burning_ship"))
		mlx->fractal = 1;
	else if (!ft_strcmp(fractal, "julia"))
		mlx->fractal = 2;
	else
	{
		ft_putstr_fd("Wrong fractal\n", 2);
		exit(-1);
	}
	ft_reset(mlx);
}

/*
** vals: 0 = color start 1 = color end 2 = color precision (shading, 1 to 100)
** (on 0 to 1000 scale for start & end, referring to preselected color values)
** 3 = value for last shading loop
*/

t_mlx	*ft_setup_mlx_p2(t_mlx *mlx)
{
	mlx->changed = 1;
	mlx->index = 0;
	mlx->indexi = 0;
	mlx->padx = 0;
	mlx->vary = 1;
	mlx->zoom = 1;
	mlx->height = 1000;
	mlx->width = 1000;
	mlx->maxiter = 1;
	mlx->autoiter = 0;
	mlx->main->img = mlx_new_image(mlx->mlx, mlx->height, mlx->width);
	mlx->main->data = mlx_get_data_addr(mlx->main->img, &mlx->main->bpx,
			&mlx->main->size, &mlx->main->end);
	mlx_mouse_hook(mlx->win, &mouse_pressed, mlx);
	mlx_key_hook(mlx->win, &key_pressed, mlx);
	mlx_loop_hook(mlx->mlx, &ft_loop, (void*)mlx);
	return (mlx);
}

t_mlx	*ft_setup_mlx(char *fractal)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	if (!(mlx->main = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	mlx->mlx = mlx_init();
	mlx->main->colors = NULL;
	mlx->colstart = 0;
	mlx->colend = 100;
	mlx->colpre = 20;
	ft_set_fractal(mlx, fractal);
	mlx->pady = 0;
	mlx->menu = NULL;
	mlx->main->nbcols = 0;
	set_colors_p1(mlx);
	mlx->moffset = 200;
	mlx->win = mlx_new_window(mlx->mlx, 1000 + mlx->moffset, 1000, "Fract'ol");
	mlx->main->img = NULL;
	mlx->xmin = -2;
	mlx->xmax = 0.5;
	mlx->ymin = -1.25;
	mlx->ymax = 1.25;
	mlx_hook(mlx->win, 6, (1L << 6), &mouse_hover, mlx);
	return (ft_setup_mlx_p2(mlx));
}

int		main(int ac, char **av)
{
	t_mlx	*mlx;

	if (ac != 2)
		return (0);
	mlx = ft_setup_mlx(av[1]);
	mlx_loop(mlx->mlx);
	return (0);
}
