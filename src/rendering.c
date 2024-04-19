/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:20:38 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 17:00:09 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_png(mlx_t *mlx, t_images *images)
{
	get_player_image(mlx, images);
	get_background_image(mlx, images);
	get_wall_image(mlx, images);
	get_collectible_image(mlx, images);
	get_exit_image(mlx, images);
	resize_images(images);
}

void	resize_images(t_images *images)
{
	int	tile_size;

	tile_size = images->tile_size;
	mlx_resize_image(images->p_image, tile_size, tile_size);
	mlx_resize_image(images->b_image, tile_size, tile_size);
	mlx_resize_image(images->w_image, tile_size, tile_size);
	mlx_resize_image(images->c_image, tile_size, tile_size);
	mlx_resize_image(images->e_image, tile_size, tile_size);
}

void	calc_tilesize(t_info *map_info)
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

void image_to_window(mlx_t *mlx, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(mlx, img, x, y) == -1)
		ft_error_mlx(mlx); 
}

void render_map(char **array, t_info *map_info, mlx_t *mlx)
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