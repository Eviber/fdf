# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 18:17:31 by ygaude            #+#    #+#              #
#    Updated: 2019/05/27 20:48:03 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror `sdl2-config --cflags`
SRC_DIR = src/
LIBFT_DIR = libft/
INCL = -I libft/ -I include/
LIBS = libft/libft.a `sdl2-config --libs` -lm -lSDL2_ttf
OBJ_DIR = obj/

SRC = draw.c drawmap.c events.c fdf_math.c genmap.c main.c parse.c sdl_tools.c \
	  tools.c wuline.c open-simplex-noise.c

OBJ = ${SRC:c=o}

all: $(NAME)

$(addprefix $(OBJ_DIR), %.o): $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCL) -c -o $@ $^

$(NAME): $(addprefix $(OBJ_DIR), $(OBJ))
	@echo "Making libft..."
	@make -C libft/
	@echo "Linking..."
	@$(CC) $(addprefix $(OBJ_DIR), $(OBJ)) -o $(NAME) $(LIBS)
	@echo "Done !"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed."

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all
