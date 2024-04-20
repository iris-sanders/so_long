/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:39:38 by irsander          #+#    #+#             */
/*   Updated: 2024/04/20 17:14:02 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_info_with_map_data(t_info *map_info, char ch)
{
	if (ch == '0')
		map_info->empty_spaces += 1;
	else if (ch == '1')
		map_info->walls += 1;
	else if (ch == 'C')
		map_info->collectibles += 1;
	else if (ch == 'E')
		map_info->exits += 1;
	else if (ch == 'P')
		map_info->players += 1;
	else if (ch == '\n')
		map_info->newlines += 1;
	else if (ch == '\0')
		map_info->endlines += 1;
	else
		ft_error("unvalid map, allowed characters: 0,1,C,E,P");
}

void	init_map_info(t_map *map_head, t_info *map_info)
{
	int		i;
	t_map	*node;

	node = map_head;
	*map_info = (t_info){0};
	while (node)
	{
		i = 0;
		while (node->line[i])
		{
			update_info_with_map_data(map_info, node->line[i]);
			i++;
		}
		node = node->next;
	}
}

void	load_png(mlx_t *mlx, t_images *images)
{
	get_player_image(mlx, images);
	get_background_image(mlx, images);
	get_wall_image(mlx, images);
	get_collectible_image(mlx, images);
	get_exit_image(mlx, images);
	resize_images(images);
}
