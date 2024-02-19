/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:23:31 by irsander          #+#    #+#             */
/*   Updated: 2024/02/19 19:16:29 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "ft_printf.h"
# include "libft.h"
# include "MLX42.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>

# define WIDTH 512
# define HEIGHT 512

//get_next_line.c
char	*get_next_line(int fd);
char	*cut_line_gnl(char *s, char *newline);
char	*find_line_gnl(char *s);
char	*ft_read_gnl(char *s, int fd);
int		ft_strlen_gnl(char *s);
int		ft_strchr_gnl(const char *s, int c);
char	*ft_strcat_gnl(char *s, char *buf);
void	*ft_free_gnl(char **s);

#endif