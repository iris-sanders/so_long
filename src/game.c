/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:29:47 by irsander          #+#    #+#             */
/*   Updated: 2024/04/20 17:41:19 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_collectibles(t_all *all, int new_y, int new_x, int tilesize)
{
	int	i;

	i = 0;
	while ((all->array[new_y][new_x] == 'C') \
			&& (all->map_info->collectibles > 0))
	{
		if ((new_x == (int)(all->map_info->im.c_image->instances[i].x \
			/ tilesize)) && (new_y == (int)(all->map_info->im.c_image-> \
			instances[i].y / tilesize)))
		{
			all->map_info->im.c_image->instances[i].enabled = false;
			all->map_info->collectibles--;
			all->array[new_y][new_x] = '0';
			break ;
		}
		i++;
	}
}

void	update_exit_and_win(t_all *all, int new_y, int new_x)
{
	if (all->map_info->collectibles == 0)
		all->map_info->im.e_image->instances[0].enabled = true;
	if (all->array[new_y][new_x] == 'E' && all->map_info->collectibles == 0)
		mlx_close_window(all->mlx);
}

void	update_player_pos(t_all *all, int x_move, int y_move, int tilesize)
{
	all->map_info->player.pos_x += x_move;
	all->map_info->player.pos_y += y_move;
	all->map_info->im.p_image->instances[0].x += x_move * tilesize;
	all->map_info->im.p_image->instances[0].y += y_move * tilesize;
}

void	move_player(t_all *all, int x_move, int y_move)
{
	int			new_x;
	int			new_y;
	int			tilesize;	
	static int	number_of_movements = 0;

	new_x = all->map_info->player.pos_x + x_move;
	new_y = all->map_info->player.pos_y + y_move;
	tilesize = all->map_info->im.tile_size;
	if (all->array[new_y][new_x] == '1')
		return ;
	collect_collectibles(all, new_y, new_x, tilesize);
	update_exit_and_win(all, new_y, new_x);
	update_player_pos(all, x_move, y_move, tilesize);
	ft_printf("\rNumber of movements: %i", number_of_movements++);
}

void	ft_keyhook(mlx_key_data_t keydata, void	*param)
{
	t_all	*all;

	all = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(all->mlx);
	else if ((keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS) || \
			(keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS))
		move_player(all, 0, -1);
	else if ((keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS) || \
			(keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS))
		move_player(all, 0, 1);
	else if ((keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS) || \
			(keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS))
		move_player(all, -1, 0);
	else if ((keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) || \
			(keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS))
		move_player(all, 1, 0);
}
