/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 19:05:42 by nboute            #+#    #+#             */
/*   Updated: 2017/04/26 15:40:13 by nboute           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# define MAGENTA 0x00FF00FF
# define RED 0x00FF0000
# define ORANGE 0x00FFA500
# define YELLOW 0x00FFFF00
# define LIME 0x0000FF00
# define GREEN 0x00008000
# define CYAN 0x0000FFFF
# define BLUE 0x000000FF
# define NAVY 0x00000080
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
}						t_img;

typedef struct			s_mlx
{
	void				*win;
	void				*mlx;
	t_img				*main;
	t_img				*menu;
	void				*img;
	void				*palet;
	char				*paletdata;

	float				zoom;
	float				xmin;
	float				xmax;
	float				ymin;
	float				ymax;
	long				ratio;
	short				itratio;
	int					maxiter;
	int					colstart;
	int					colend;
	int					colpre;
	int					colrange;
	int					moffset;

	int					width;
	int					*colors;
	int					nbcols;
	int					height;
	int					gwid;
	int					ghei;
}						t_mlx;

void	draw_menu(t_mlx *mlx);

#endif
