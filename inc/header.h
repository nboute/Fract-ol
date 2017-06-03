/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 19:05:42 by nboute            #+#    #+#             */
/*   Updated: 2017/06/03 18:47:14 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define MAGENTA 0x00FF00FF
# define RED 0x00FF0000
# define ORANGE 0x00FFA500
# define YELLOW 0x00FFFF00
# define LIME 0x0000FF00
# define GREEN 0x00006600
# define CYAN 0x0000FFFF
# define BLUE 0x000000FF
# define NAVY 0x00000080
# define DARKTURQUOISE 0x00004D39
# define PURPLE 0x00800080
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define MAX_COLS 1000
# define ABS(value) (value < 0) ? (-1 * value) : value

# include "../libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../minilibx_macos/mlx.h"

typedef struct			s_readlines
{
	char				**tab;
	struct s_readlines	*next;
}						t_readlines;

typedef struct			s_img
{
	void				*img;
	char				*data;
	int					bpx;
	int					end;
	int					size;
	int					*colors;
	int					nbcols;
}						t_img;

/*
**
** 1 mandelbrot
** 2 julia
** 3 burning_ship
** 4
**
*/

typedef struct			s_mlx
{
	void				*win;
	void				*mlx;
	t_img				*main;
	t_img				*menu;
	void				*img;

	float				xmin;
	float				xmax;
	float				ymin;
	float				ymax;
	double				padx;
	double				pady;
	long				zoom;
	short				itratio;
	int					maxiter;
	short				autoiter;
	int					colstart;
	int					colend;
	int					colpre;
	int					colrange;
	int					index;
	int					moffset;
	int					mval;
	int					fractal;
	int					palstart;
	int					palend;
	int					vary;

	int					width;
	int					height;
	int					gwid;
	int					ghei;
}						t_mlx;

typedef struct			s_fractal
{
	char				*name;
	int					id;
	void				(*fct)(int x, int y, t_mlx *mlx);
}						t_fractal;


void	draw_menu(t_mlx *mlx);
int		*set_color_values(int vals[3], int *nbcols, int **colors);
int		set_colors_p1(t_mlx *mlx);
void	ft_place_pixel(int color, int x, int y, t_img *img);
int		menu_action(int x, int y, t_mlx *mlx, int button);

#endif
