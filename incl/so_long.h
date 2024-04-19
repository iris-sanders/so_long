/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:23:31 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 15:15:10 by irsander         ###   ########.fr       */
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
# include <stdbool.h>

# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_map {
	char			*line;
	int				length;
	struct s_map	*next;
} t_map;

typedef struct s_images {
	mlx_texture_t	*p_texture;
	mlx_image_t		*p_image;
	mlx_texture_t	*b_texture;
	mlx_image_t		*b_image;
	mlx_texture_t	*w_texture;
	mlx_image_t		*w_image;
	mlx_texture_t	*c_texture;
	mlx_image_t		*c_image;
	mlx_texture_t	*e_texture;
	mlx_image_t		*e_image;
	int				tile_size;
	
} t_images;

typedef struct s_player {
	int	pos_x;
	int	pos_y;
}t_player;

typedef struct s_col {
	int pos_x;
	int pos_y;
}t_col;

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
	t_images im;
	t_player player;
	t_col col;
} t_info;

typedef struct s_all {
	t_info	*map_info;
	mlx_t	*mlx;
	char	**array;
} t_all;


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
char	**parse_map(char *file, t_info *map_info);
void	validate_map(t_map *map_head, t_info *map_info);

//parse_map_utils.c
t_map	*create_node(char *data);
void	node_add_back(t_map **head, t_map *new_node);
size_t	line_strlen(const char *s);
void	print_list(t_map *head);
void	ft_error(char *msg);

void 	ft_error_mlx(mlx_t *mlx);
void	free_2d_array(char **array);




#endif