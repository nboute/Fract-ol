# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nboute <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/04 20:02:22 by nboute            #+#    #+#              #
#    Updated: 2017/06/21 18:16:10 by nboute           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: make all clean fclean re

NAME = fractol

LIB = -L libft/ -lft

LIBFT = libft/libft.a

MLX = -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit

LIBMLX = minilibx_macos/mlx.a

PTHREAD = -lpthread -D_REENTRANT

CFLAGS = -c -Wall -Wextra -Werror

OPTI = -O3 -march=native

WFLAGS = -Wall -Wextra -Werror

CC = gcc

C_DIR = srcs/

SRCS = ft_actions.c \
	   menu.c \
	   ft_colors.c \
	   ft_fractals.c \
	   ft_keys.c \
	   ft_setcolors.c \
	   ft_setup.c \
	   ft_draw.c

SRC = $(addprefix $(C_DIR), $(SRCS))

OBJ = $(SRCS:.c=.o)

INC = -I includes -I libft/


all : $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OPTI) $(WFLAGS) $(MLX) $^ -o $@ $(LIB) $(PTHREAD)

$(LIBFT):
	make -C libft/

$(LIBMLX):
	make -C minilibx_macos/

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) $^ $(INC)

clean :
	make clean -C libft/
	make clean -C minilibx_macos/
	rm -f $(OBJ)

fclean : clean
	rm -f $(LIBFT)
	rm -f $(LIBMLX)
	rm -f libft.a
	rm -f $(NAME)

re : fclean all
