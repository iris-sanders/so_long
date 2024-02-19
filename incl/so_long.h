/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:23:31 by irsander          #+#    #+#             */
/*   Updated: 2024/02/19 16:07:31 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "ft_printf.h"
# include "libft.h"
# include "../lib/MLX42_linux/include/MLX42/MLX42.h"
# include "../lib/MLX42_macos/include/MLX42/MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>

# define WIDTH 512
# define HEIGHT 512

//get_next_line.c
char	*cut_line(char *s, char *newline);
char	*find_line(char *s);
char	*ft_read(char *s, int fd);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
int		ft_strchr(const char *s, int c);
char	*ft_strcat(char *s, char *buf);
void	*ft_free(char **s);

#endif