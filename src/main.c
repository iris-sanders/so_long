/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:17:37 by irsander          #+#    #+#             */
/*   Updated: 2024/04/10 22:41:09 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	resize_images(t_images *images)
{
	int	tile_size;

	tile_size = images->tile_size;
	mlx_resize_image(images->p_image, tile_size, tile_size);
	mlx_resize_image(images->b_image, tile_size, tile_size);
	mlx_resize_image(images->w_image, tile_size, tile_size);
	mlx_resize_image(images->c_image, tile_size, tile_size);
	mlx_resize_image(images->e_image, tile_size, tile_size);
}

static void get_player_image(mlx_t *mlx, t_images *images)
{
	images->p_texture = mlx_load_png("sprites/fox.png");
	if (!images->p_texture)
		ft_error("failed to load player png");
	images->p_image = mlx_texture_to_image(mlx, images->p_texture);
	if (!images->p_image)
		ft_error("failed to create player image");
}

static void get_background_image(mlx_t *mlx, t_images *images)
{
	images->b_texture = mlx_load_png("sprites/background.png");
	if (!images->b_texture)
		ft_error ("failed to load background png");
	images->b_image = mlx_texture_to_image(mlx, images->b_texture);
	if (!images->b_image)
		ft_error("failed to create background image");
}

static void get_wall_image(mlx_t *mlx, t_images *images)
{
	images->w_texture = mlx_load_png("sprites/tree.png");
	if (!images->w_texture)
		ft_error ("failed to load wall png");
	images->w_image = mlx_texture_to_image(mlx, images->w_texture);
	if (!images->w_image)
		ft_error("failed to create wall image");
}

static void get_collectible_image(mlx_t *mlx, t_images *images)
{
	images->c_texture = mlx_load_png("sprites/flower.png");
	if (!images->c_texture)
		ft_error ("failed to load collectible png");
	images->c_image = mlx_texture_to_image(mlx, images->c_texture);
	if (!images->c_image)
		ft_error("failed to create collectible image");
}

static void get_exit_image(mlx_t *mlx, t_images *images)
{
	images->e_texture = mlx_load_png("sprites/portal.png");
	if (!images->e_texture)
		ft_error ("failed to load exit png");
	images->e_image = mlx_texture_to_image(mlx, images->e_texture);
	if (!images->e_image)
		ft_error("failed to create exit image");
}

static void	get_png(mlx_t *mlx, t_images *images)
{
	get_player_image(mlx, images);
	get_background_image(mlx, images);
	get_wall_image(mlx, images);
	get_collectible_image(mlx, images);
	get_exit_image(mlx, images);
	resize_images(images);
}

static void calc_tilesize(t_info *map_info)
{
	int	x_tile;
	int	y_tile;
	int small_size;
	
	x_tile = WIDTH / map_info->x_length;
	y_tile = HEIGHT / map_info->y_length;
	small_size = x_tile;
	if (small_size > y_tile)
		small_size = y_tile;
	map_info->im.tile_size = small_size;
}
static void image_to_window(mlx_t *mlx, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(mlx, img, x, y) == -1)
		ft_error_mlx(mlx); 
}

static void render_map(char **array, t_info *map_info, mlx_t *mlx)
{
	int x;
	int y;
	int tile_size;

	tile_size = map_info->im.tile_size;
	y = 0;
	while (array[y])
	{
		x = 0;
		while (array[y][x])
		{
			image_to_window(mlx, map_info->im.b_image, tile_size * x, tile_size * y);
			if (array[y][x] == '1')
				image_to_window(mlx, map_info->im.w_image, tile_size * x, tile_size * y);
			if (array[y][x] == 'C')
				image_to_window(mlx, map_info->im.c_image, tile_size * x, tile_size * y);
			if (array[y][x] == 'E')
			{
				image_to_window(mlx, map_info->im.e_image, tile_size * x, tile_size * y);
				map_info->im.e_image->instances[0].enabled = false;
			}
			x++;
		}
		y++;
	}
	image_to_window(mlx, map_info->im.p_image, tile_size * map_info->player.pos_x, tile_size * map_info->player.pos_y);
}

void ft_error_mlx(mlx_t *mlx)
{
	if (mlx)
		mlx_close_window(mlx);
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void update_player_pos(t_all *all, int x_move, int y_move) 
{
	int new_x;
	int new_y;
	int tilesize;

	new_x = all->map_info->player.pos_x + x_move;
	new_y = all->map_info->player.pos_y + y_move;
	tilesize = all->map_info->im.tile_size;
	if (all->array[new_y][new_x] == '1')
		return;
	int i = 0;
	while ((all->array[new_y][new_x] == 'C') && (all->map_info->collectibles > 0))
	{
		if ((new_x == (int)(all->map_info->im.c_image->instances[i].x / tilesize)) && \
		(new_y == (int)(all->map_info->im.c_image->instances[i].y / tilesize)))
		{
			all->map_info->im.c_image->instances[i].enabled = false;
			all->map_info->collectibles--;
			all->array[new_y][new_x] = '0';
			break;
		}
		i++;
	}
	if (all->map_info->collectibles == 0)
		all->map_info->im.e_image->instances[0].enabled = true;	
	all->map_info->player.pos_x += x_move;
	all->map_info->player.pos_y += y_move;
	all->map_info->im.p_image->instances[0].x += x_move * tilesize;
	all->map_info->im.p_image->instances[0].y += y_move * tilesize;
}

void ft_keyhook(mlx_key_data_t keydata, void* param)
{
	t_all* all = param;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(all->mlx);
	else if ((keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS) ||\
			(keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS))
		update_player_pos(all, 0, -1);
	else if ((keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS) ||\
			(keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS))
		update_player_pos(all, 0, 1);
	else if ((keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) ||\
			(keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS))
		update_player_pos(all, -1, 0);
	else if ((keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) ||\
			(keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS))
		update_player_pos(all, 1, 0);
}

int32_t main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_info		map_info;
	char		**array;
	t_all		all_info;

	if (argc != 2)
	{
		ft_putstr_fd("Error: invalid numer of arguments\n", STDERR_FILENO);
		ft_putstr_fd("<name_of_program> <path_to_map_file>\n", STDERR_FILENO); //What is stder_fileno // why to use it
		exit(EXIT_FAILURE);
	}
	array = parse_map(argv[1], &map_info);
	calc_tilesize(&map_info);
	if (!(mlx = mlx_init(map_info.x_length * map_info.im.tile_size, \
						 map_info.y_length * map_info.im.tile_size, "MLX42", false)))
		ft_error_mlx(mlx);
	get_png(mlx, &map_info.im);
	render_map(array, &map_info, mlx);
	all_info = (t_all){&map_info, mlx, array};
	mlx_key_hook(mlx, &ft_keyhook, &all_info);
	// update_collectibles(&all_info, &map_info.player, &map_info.col); // not working, implement linked list for pos of collectibles
	// valid_exit() are collectibles 0
	// all_info.map_info = &map_info;
	// all_info.mlx = mlx;
	// all_info.array = array;
	// mlx_loop_hook(mlx, ft_randomize, &all_info);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

