/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:23:31 by irsander          #+#    #+#             */
/*   Updated: 2024/03/11 15:29:17 by irsander         ###   ########.fr       */
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

# define WIDTH 720
# define HEIGHT 405

typedef struct s_map {
	char			*line;
	int				length;
	struct s_map	*next;
} t_map;

typedef struct s_info {
	int	empty_spaces; //might not need
	int	walls; //might not need
	int collectibles; 
	int exits; 
	int players;
	int newlines; //might not need
	int endlines;
	int	x_length;
	int	y_length;
} t_info;

typedef struct s_player {
	int	pos_x;
	int	pos_y;
}t_player;


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
t_map	*open_map(char *file);
t_map	*parse_map(char *file, t_info *map_info, t_player *player_info);
void	validate_map(t_map *map_head, t_info *map_info);

//parse_map_utils.c
t_map	*create_node(char *data);
void	node_add_back(t_map **head, t_map *new_node);
size_t	line_strlen(const char *s);
void	print_list(t_map *head);
void	ft_error(char *msg);




#endif