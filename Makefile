# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irsander <irsander@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/12 13:26:39 by irsander          #+#    #+#              #
#    Updated: 2024/02/12 14:11:33 by irsander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#C compiler
CC		=	cc

#Flags
CFLAGS	=	-Wall -Wextra -Werror

#Target name
NAME	=	so_long

#Directories
LIB_DIR	=	./lib
OBJ_DIR	=	./src/obj
SRC_DIR	=	./src

#Include directories
INCL	=	-I ./incl -I $(LIB_DIR)/libft -I $(LIB_DIR)/ft_printf

#Source files
FILES	=	main.c

SRC		=	$(addprefix $(SRC_DIR)/, $(FILES))	
OBJ		=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

#Library dependencies
LIBFT	=	$(LIB_DIR)/libft/libft.a
PRINTF	=	$(LIB_DIR)/ft_printf/libftprintf.a

#Build rule
all: $(NAME)

#Executable rule
$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	$(CC) $^ $(INCL) $(CFLAGS) -o $(NAME)

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

#Full clean rule
fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIB_DIR)/ft_printf
	$(MAKE) fclean -C $(LIB_DIR)/libft

#Rebuild rule
re: fclean all

#Phony targets
.PHONY: all clean make fclean re