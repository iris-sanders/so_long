/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:31:15 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 19:35:55 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	floodfill(char **temp_array, int x, int y, t_info *map_info)
{
	static int	collected_c;
	static int	exit_is_reachable;

	if (collected_c == map_info->collectibles && exit_is_reachable == 1)
		return (true);
	if (temp_array[y][x] == '1')
		return (false);
	if (temp_array[y][x] == 'C')
		collected_c++;
	if (temp_array[y][x] == 'E')
		exit_is_reachable++;
	temp_array[y][x] = '1';
	if (floodfill(temp_array, x +1, y, map_info) ||
		floodfill(temp_array, x -1, y, map_info) ||
		floodfill(temp_array, x, y +1, map_info) ||
		floodfill(temp_array, x, y -1, map_info))
		return (true);
	return (false);
}

void	player_pos(char **temp_array, t_info *map_info)
{
	int x;
	int y;
	
	y = 0;
	while (y < map_info->y_length)
	{
		x = 0;
		while (x < map_info->x_length)
		{
			if (temp_array[y][x] == 'P')
			{
				map_info->player.pos_y = y;
				map_info->player.pos_x = x;
				break;
			}
			x++;
		}
		y++;
	}
}

char	**copy_array(char **temp_array, t_info *map_info)
{
	char	**array;
	int		y;
	
	y = map_info->y_length;
	array = malloc((y + 1) * sizeof(char *));
	if (!array)
		ft_error("failed to allocate memory");
	array[y] = NULL;
	y--;
	while (y >= 0)
	{
		array[y] = ft_strdup(temp_array[y]);
		if (!array[y])
		{
			free_2d_array(array);
			ft_error("failed to allocate memory for string copy");
			return NULL;
		}
		y--;
	}
	array[map_info->y_length] = NULL;
	return (array);
}

char	**list_to_2d_array(t_map *map_head, t_info *map_info)
{
	t_map	*next_node;
	char	**array;
	int		i;

	map_info->y_length = count_nodes(map_head);
	map_info->x_length = ft_strlen(map_head->line);
	array = malloc((map_info->y_length + 1) * sizeof(char *));
	if (!array)
		ft_error("memory allocation failed");
	i = 0;
	while (map_head)
	{
		array[i] = map_head->line;
		i++;
		next_node = map_head->next;
		free(map_head);
		map_head = next_node;
	}
	array[i] = NULL;
	return (array);
}

char	**path_is_valid(t_map *map_head, t_info *map_info, char **array)
{
	char	**temp_array;
	
	temp_array = list_to_2d_array(map_head, map_info);
	array = copy_array(temp_array, map_info);
	player_pos(temp_array, map_info);
	if (floodfill(temp_array, map_info->player.pos_x, map_info->player.pos_y, map_info) == false)
		ft_error("No valid path");
	free_2d_array(temp_array);
	return (array);
}