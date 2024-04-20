/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:20:38 by irsander          #+#    #+#             */
/*   Updated: 2024/04/20 17:12:58 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	int	small_size;

	x_tile = WIDTH / map_info->x_length;
	y_tile = HEIGHT / map_info->y_length;
	small_size = x_tile;
	if (small_size > y_tile)
		small_size = y_tile;
	map_info->im.tile_size = small_size;
}

void	image_to_window(mlx_t *mlx, mlx_image_t *img, int x, int y)
{
	if (mlx_image_to_window(mlx, img, x, y) == -1)
		ft_error_mlx(mlx);
}

void	render_images(t_all *all_info, int tile_size, int y)
{
	int	x;

	while (all_info->array[y])
	{
		x = 0;
		while (all_info->array[y][x])
		{
			image_to_window(all_info->mlx, all_info->map_info->im.b_image, \
							tile_size * x, tile_size * y);
			if (all_info->array[y][x] == '1')
				image_to_window(all_info->mlx, all_info->map_info->im.w_image, \
								tile_size * x, tile_size * y);
			if (all_info->array[y][x] == 'C')
				image_to_window(all_info->mlx, all_info->map_info->im.c_image, \
								tile_size * x, tile_size * y);
			if (all_info->array[y][x] == 'E')
			{
				image_to_window(all_info->mlx, all_info->map_info->im.e_image, \
								tile_size * x, tile_size * y);
				all_info->map_info->im.e_image->instances[0].enabled = false;
			}
			x++;
		}
		y++;
	}
}

void	render_map(t_all *all_info)
{
	int	y;
	int	tile_size;

	tile_size = all_info->map_info->im.tile_size;
	y = 0;
	render_images(all_info, tile_size, y);
	image_to_window(all_info->mlx, all_info->map_info->im.p_image, \
					tile_size * all_info->map_info->player.pos_x, \
					tile_size * all_info->map_info->player.pos_y);
}
