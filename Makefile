# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 13:26:39 by irsander          #+#    #+#              #
#    Updated: 2024/02/12 22:07:25 by irsander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#C compiler
CC		=	cc

#Flags
CFLAGS	=	-Wall -Wextra -Werror
MLXFLAG	=	-framework Cocoa -framework OpenGL -framework IOKit -lglfw

#Target name
NAME	=	so_long

#Directories
LIB_DIR	=	lib
OBJ_DIR	=	src/obj
SRC_DIR	=	src

#Include directories
INCL	=	-I ./incl -I $(LIB_DIR)/libft -I $(LIB_DIR)/ft_printf -I $(LIB_DIR)/MLX42/include

#Source files
FILES	=	main.c \

SRC		=	$(addprefix $(SRC_DIR)/, $(FILES))	
OBJ		=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

#Library dependencies
LIBFT	=	$(LIB_DIR)/libft/libft.a
PRINTF	=	$(LIB_DIR)/ft_printf/libftprintf.a
MLX		=	$(LIB_DIR)/MLX42/build/libmlx42.a

#Build rule
all: $(MLX) $(NAME)

$(MLX):
	@cmake $(LIB_DIR) -B $(LIB_DIR)/MLX42/build && make -C $(LIB_DIR)/MLX42/build -j4

#Executable rule
$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(MLX)
	$(CC) $^ $(INCL) $(CFLAGS) $(MLXFLAG) -o $(NAME)

#Library build rule
$(PRINTF):
	make -C $(LIB_DIR)/ft_printf

#Library build rule
$(LIBFT):
	make -C $(LIB_DIR)/libft

#Object directory rule
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

#Object compilation rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -c $< $(INCL) $(CFLAGS) -o $@ 

#Clean rule
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIB_DIR)/ft_printf
	$(MAKE) clean -C $(LIB_DIR)/libft
	rm -rf $(MLX_DIR)/build

#Full clean rule
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)/ft_printf
	$(MAKE) fclean -C $(LIB_DIR)/libft

#Rebuild rule
re: fclean all

#Phony targets
.PHONY: all clean make fclean re