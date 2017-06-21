/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboute <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 19:05:42 by nboute            #+#    #+#             */
/*   Updated: 2017/06/21 18:34:24 by nboute           ###   ########.fr       */
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
# define ABS(value) (value < 0) ? -value : value

# include "../libft/libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../minilibx_macos/mlx.h"
# include <pthread.h>

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
** 1 mandelbrot
** 2 julia
** 3 burning_ship
** 4
*/

typedef struct			s_mlx
{
	void				*win;
	void				*mlx;
	t_img				*main;
	t_img				*menu;
	int					pixels[1000][1000];

	int					changed;
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
	int					indexi;
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

typedef struct			s_thread
{
	struct s_mlx		*mlx;
	int					part;
	pthread_t			thread;
}						t_thread;

void					draw_menu(t_mlx *mlx);
void					menu_action(int x, int y, t_mlx *mlx, int button);
int						mouse_pressed(int button, int x, int y, void *param);
void					ft_move_cursor(t_mlx *mlx, double x, double y);
int						mouse_hover(int x, int y, void *param);
int						set_color(int cp);
int						ft_gradation(unsigned int col, unsigned int col2,
		int p);
int						get_color_grad(int val, int val2, int pre, int perc);
int						set_colors_p1(t_mlx *mlx);
int						*set_color_values(int vals[4], int *nbcols,
		int **colors);
void					ft_place_pixel(int color, int x, int y, t_img *img);
int						ft_loop(void *pass);
void					*draw_fractal(void *thread);
void					ft_reset(t_mlx *mlx);
int						key_pressed(int key, void *ptr);
void					julia(int x, int y, t_mlx *mlx);
void					mandelbrot(int x, int y, t_mlx *mlx);
void					burning_ship(int x, int y, t_mlx *mlx);
void					ft_set_fractal(t_mlx *mlx, char *fractal);
void					get_palet(int **colors, int *nbcols);
void					setup_menu(t_mlx *mlx);
void					draw_palet(t_img *menu, int offset, int colstart,
		int colend);

#endif
