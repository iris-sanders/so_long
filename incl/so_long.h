/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:23:31 by irsander          #+#    #+#             */
/*   Updated: 2024/02/29 18:59:30 by irsander         ###   ########.fr       */
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

typedef struct s_map {
	char			*line;
	int				length;
	struct s_map	*next;
} t_map;

typedef struct s_info {
	int	empty_spaces;
	int	walls;
	int collectibles;
	int exits;
	int players;
	int newlines;
	int endlines;
} t_info;

typedef struct player {
	int	steps;
	int	x;
	int	y;
} player;


//get_next_line.c
char	*get_next_line_gnl(int fd);
char	*cut_line_gnl(char *s, char *newline);
char	*find_line_gnl(char *s);
char	*ft_read_gnl(char *s, int fd);
int		ft_strlen_gnl(char *s);
int		ft_strchr_gnl(const char *s, int c);
char	*ft_strcat_gnl(char *s, char *buf);
void	*ft_free_gnl(char **s);

//parse_map.c
t_map	*open_file(char *file);
t_map	*map_init(char *file, t_info *map_info);
void	validate_map(t_map *map_head, t_info *map_info);

#endif