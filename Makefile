# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 18:17:31 by ygaude            #+#    #+#              #
#    Updated: 2017/10/18 22:16:43 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src/
LIBFT_DIR = libft/
INCL =  -I libft/ -I include/ -I minilibx_macos/
LIBS = libft/libft.a minilibx_macos/libmlx.a -framework OpenGL -framework AppKit
OBJ_DIR = obj/

SRC = draw.c drawmap.c events.c fdf_math.c genmap.c main.c parse.c tools.c     \
	  wuline.c

OBJ = ${SRC:c=o}

all: $(NAME)

%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCL) -c -o $(OBJ_DIR)$@ $^

$(NAME): $(OBJ)
	@echo "Making libft..."
	@make -C libft/
	@echo "Linking..."
	@$(CC) $(CFLAGS) $(INCL) $(LIBS) $(addprefix $(OBJ_DIR), $(OBJ)) -o $(NAME)
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
