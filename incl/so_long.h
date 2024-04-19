/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:23:31 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 19:49:59 by irsander         ###   ########.fr       */
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
	t_images	*imgs;
} t_all;

//game.c
void 	collect_collectibles(t_all *all, int new_y, int new_x, int tilesize);
void	update_exit_and_win(t_all *all, int new_y, int new_x);
void	update_player_pos(t_all *all, int x_move, int y_move, int tilesize);
void 	move_player(t_all *all, int x_move, int y_move);
void 	ft_keyhook(mlx_key_data_t keydata, void* param);

//get_next_line_utils.c
void	*ft_free_gnl(char **s);
int		ft_strlen_gnl(char *s);
int		ft_strchr_gnl(const char *s, int c);
char	*ft_strcat_gnl(char *s, char *buf);

//get_next_line.c
char	*cut_line_gnl(char *s, char *newline);
char	*find_line_gnl(char *s);
char	*get_next_line_gnl(int fd);

//linked_list.c
t_map	*create_node(char *data);
void	node_add_back(t_map **head, t_map *new_node);
void	print_list(t_map *head);
int		count_nodes(t_map *map_head);

//map_init.c
void	update_info_with_line_data(t_info *map_info, char ch);
void 	init_map_info(t_map *map_head, t_info *map_info);

//parse_map.c
t_map	*open_map(char *file);
char	**parse_map(char *file, t_info *map_info);

//map_init.c
void	update_info_with_map_data(t_info *map_info, char ch);
void 	init_map_info(t_map *map_head, t_info *map_info);

// rendering.c
void	load_png(mlx_t *mlx, t_images *images);
void	resize_images(t_images *images);
void	calc_tilesize(t_info *map_info);
void image_to_window(mlx_t *mlx, mlx_image_t *img, int x, int y);
void render_map(char **array, t_info *map_info, mlx_t *mlx);

// sprites.c
void	get_player_image(mlx_t *mlx, t_images *images);
void 	get_background_image(mlx_t *mlx, t_images *images);
void	get_wall_image(mlx_t *mlx, t_images *images);
void	get_collectible_image(mlx_t *mlx, t_images *images);
void	get_exit_image(mlx_t *mlx, t_images *images);

//utils.c
size_t	line_strlen(const char *s);
void	free_2d_array(char **array);
void	ft_error(char *msg);
void 	cleanup(t_all *all_info, char **array);
void 	ft_error_mlx(mlx_t *mlx);

//validate_map.c
int		map_is_rectangular(t_map *map_head);
void	check_map_side_walls(t_map *map_head);
void	check_map_top_bottom_walls(t_map *map_head);
int		check_map_info(t_info *map_info);
void	map_is_valid(t_info *map_info, t_map *map_head);

//validate_path.c
bool	floodfill(char **temp_array, int x, int y, t_info *map_info);
void	player_pos(char **temp_array, t_info *map_info);
char	**copy_array(char **temp_array, t_info *map_info);
char	**list_to_2d_array(t_map *map_head, t_info *map_info);
char	**path_is_valid(t_map *map_head, t_info *map_info, char **array);

#endif