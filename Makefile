# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/08 15:43:37 by mzblah            #+#    #+#              #
#    Updated: 2021/05/30 22:51:14 by mzblah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

DIR = ~/Users/mzblah/Desktop/cub3d/

LIBFT = libft.a

LIBFT_PATH = libft

SRCS_PATH = ./srcs/

BONUS_PATH = $(SRCS_PATH)bonus/

EXIT_SRCS_PATH = $(SRCS_PATH)exit_management/

READ_CUB_PATH = $(SRCS_PATH)parse_read_cub/

GAME_PATH = $(SRCS_PATH)game/

HEADER = ./includes/

GNL_HEADER = ./gnl/

MLX_PATH = ./Mlx/

SRCS =			$(GNL_HEADER)get_next_line_utils.c			\
				$(GNL_HEADER)get_next_line.c				\
				$(SRCS_PATH)cub3d.c 						\
				$(READ_CUB_PATH)cub3d_parse_cub.c			\
				$(READ_CUB_PATH)cub3d_parse_cub_color_res.c	\
				$(READ_CUB_PATH)cub3d_parse_map.c			\
				$(READ_CUB_PATH)cub3d_read_map.c			\
				$(GAME_PATH)game_init.c						\
				$(GAME_PATH)game_raycasting.c				\
				$(GAME_PATH)game_move.c						\
				$(GAME_PATH)game_texture_pixels.c			\
				$(GAME_PATH)game_init_img_textures.c		\
				$(GAME_PATH)game_raycasting_sprite.c		\
				$(EXIT_SRCS_PATH)cub3d_exit_management.c 	\
				$(EXIT_SRCS_PATH)cub3d_error_message.c 

BONUS_SRCS =	$(BONUS_PATH)game_init_bonus.c				\
				$(BONUS_PATH)minimap_bonus.c				\
				$(BONUS_PATH)hud_bonus.c					\
				$(BONUS_PATH)weapon_bonus.c					\
				$(BONUS_PATH)init_hud_bonus.c				\
				$(BONUS_PATH)game_move_bonus.c				\
				$(BONUS_PATH)cub3d_parse_map_bonus.c		\
				$(BONUS_PATH)game_init_img_textures_bonus.c	\
				$(BONUS_PATH)cub3d_exit_management_bonus.c 	\
				$(BONUS_PATH)cub3d_free_bonus.c			 	\
				$(BONUS_PATH)cub3d_parse_cub_bonus.c		\
				$(GNL_HEADER)get_next_line_utils.c			\
				$(GNL_HEADER)get_next_line.c				\
				$(SRCS_PATH)cub3d.c 						\
				$(READ_CUB_PATH)cub3d_parse_cub_color_res.c	\
				$(READ_CUB_PATH)cub3d_read_map.c			\
				$(GAME_PATH)game_raycasting.c				\
				$(GAME_PATH)game_texture_pixels.c			\
				$(GAME_PATH)game_raycasting_sprite.c		\
				$(EXIT_SRCS_PATH)cub3d_error_message.c 

OBJS = $(SRCS:.c=.o)

OBJS_BONUS = $(BONUS_SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit

.c.o:
	cc $(CFLAGS) -c $< -o $@ -I $(HEADER) -I $(LIBFT_PATH) -I $(GNL_HEADER) -I ./Mlx/
	
all: $(NAME)

sanitize: $(OBJS) libft
	clang -g3 -fsanitize=address $(CFLAGS) $(OBJS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L ./Mlx ./Mlx/libmlx.a -lXext -lX11 -lm

$(NAME): $(OBJS) libft mlx
	clang $(CFLAGS) $(OBJS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L ./Mlx ./Mlx/libmlx.a -lXext -lX11 -lm

bonus: $(OBJS_BONUS) libft mlx
	clang $(CFLAGS) $(OBJS_BONUS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L ./Mlx ./Mlx/libmlx.a -lXext -lX11 -lm

bonuss: $(OBJS_BONUS) libft mlx
	clang -g3 -fsanitize=address $(OBJS_BONUS) $(LIBFT_PATH)/$(LIBFT) -o $(NAME) -L ./Mlx ./Mlx/libmlx.a -lXext -lX11 -lm

libft:
	make -C $(LIBFT_PATH)

mlx:
	make -C $(MLX_PATH)

norm:
	 norminette $(SRCS) $(BONUS_SRCS) ./includes/cub3d.h ./gnl/get_next_line.h libft/ft_atoi.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_chr_in_str.c libft/ft_isalnum.c libft/ft_isalpha.c libft/ft_isascii.c libft/ft_isdigit.c libft/ft_isprint.c libft/ft_isspace.c libft/ft_memccpy.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_putchar.c libft/ft_putchar_fd.c libft/ft_putendl_fd.c libft/ft_putnbr.c libft/ft_putnbr_fd.c libft/ft_putstr.c libft/ft_putstr_fd.c libft/ft_strcat.c libft/ft_strcmp.c libft/ft_strcpy.c libft/ft_strdup.c libft/ft_strlcat.c libft/ft_strlen.c libft/ft_strncat.c libft/ft_strncmp.c libft/ft_strncpy.c libft/ft_strnew.c libft/ft_tolower.c libft/ft_toupper.c libft/libft.h

clibft:
	make clean -C $(LIBFT_PATH)

fclibft:
	make fclean -C $(LIBFT_PATH)

clean: clibft
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -rf $(NAME) $(LIBFT_PATH)/$(LIBFT)
	make clean -C $(MLX_PATH)

re: fclean all

launch: all
	./$(NAME)

flaunch: fclean launch

.PHONY: all clean fclean re norm launch flaunch libft clibft fclibft
