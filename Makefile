# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: iboeters <iboeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/31 18:42:32 by iboeters      #+#    #+#                  #
#    Updated: 2020/09/09 21:25:14 by iboeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = cub3d.c \
	./parsing/parse.c \
	./parsing/parse_utils.c \
	./parsing/parse_utils_2.c \
	./parsing/parse_utils_3.c \
	./parsing/identifier_functions.c \
	./parsing/save_map.c \
	./parsing/check_map.c \
	./parsing/make_map_array.c \
	./parsing/get_next_line.c \
	./parsing/get_next_line_utils.c \
	./raycasting/raycast_loop.c \
	./raycasting/rotate.c \
	./raycasting/textures.c \
	./raycasting/sprites.c \
	./raycasting/raycast_setup.c \
	./raycasting/dda.c \
	./raycasting/move.c \
	color.c \
	key_pressed.c \
	save_sprites.c \
	screenshot.c \
	free_arrays.c

OBJ = $(SRC:.c=.o)

LIB = -Lmlx -lmlx -framework OpenGL -framework AppKit -lm

MLX = libmlx.dylib

all: $(NAME)

$(NAME): $(OBJ)
	@make -C ./mlx
	@make -C ./libft
	cp ./mlx/$(MLX) .
	gcc -Wall -Werror -Wextra $^ -I cubed.h -Llibft -lft $(LIB) -o $(NAME)

clean:
	@make -C ./mlx clean
	@make -C ./libft fclean
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	rm -f $(MLX)

re:	fclean all
