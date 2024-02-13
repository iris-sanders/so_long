# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 13:26:39 by irsander          #+#    #+#              #
#    Updated: 2024/02/13 19:49:37 by irsander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = $(shell uname)

ifeq ($(UNAME), Linux)
    LFLAGS = -ldl -lglfw -pthread -lm
	MLX_DIR	= lib/MLX42_linux
endif
ifeq ($(UNAME), Darwin)
    LFLAGS = -framework Cocoa -framework OpenGL -framework IOKit -lglfw
	MLX_DIR = lib/MLX42_macos
endif

NAME	=	so_long

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

LIB_DIR	=	lib
OBJ_DIR	=	src/obj
SRC_DIR	=	src

INCL	=	-I ./incl -I $(LIB_DIR)/libft -I $(LIB_DIR)/ft_printf -I $(LIB_DIR)/$(MLX_DIR)/include

FILES	=	main.c \

SRC		=	$(addprefix $(SRC_DIR)/, $(FILES))	
OBJ		=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

LIBFT	=	$(LIB_DIR)/libft/libft.a
PRINTF	=	$(LIB_DIR)/ft_printf/libftprintf.a
MLX		=	$(LIB_DIR)/$(MLX_DIR)/build/libmlx42.a

all: $(MLX) $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $^ $(INCL) $(CFLAGS) $(LFLAGS) -o $(NAME)
	
$(MLX):
	@cmake $(MLX_DIR) -B $(LIB_DIR)/$(MLX_DIR)/build && make -C $(LIB_DIR)/$(MLX_DIR)/build -j4

$(PRINTF):
	make -C $(LIB_DIR)/ft_printf

$(LIBFT):
	make -C $(LIB_DIR)/libft

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< $(INCL) $(CFLAGS) -o $@ 

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)/ft_printf
	$(MAKE) clean -C $(LIB_DIR)/libft
	rm -rf $(MLX_DIR)/build

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)/ft_printf
	$(MAKE) fclean -C $(LIB_DIR)/libft

re: fclean all

.PHONY: all clean make fclean re