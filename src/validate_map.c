/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:47:45 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 20:12:38 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_is_rectangular(t_map *map_head)
{
	t_map	*node;

	node = map_head;
	while (node->next)
	{
		if (!(node->length == node->next->length))
			ft_error("map is not rectangular");
		node = node->next;	
	}
	return (0);
}
void	check_map_side_walls(t_map *map_head)
{
	t_map	*node;
	int		i;
	
	node = map_head;
	while (node)
	{
		i = node->length -1;
		if ((node->line[0] != '1') || (node->line[i] != '1'))
			ft_error("side of map not surrounded by wall");
		node = node->next;
	}
}

void	check_map_top_bottom_walls(t_map *map_head)
{
	t_map	*first_node;
	t_map	*last_node;
	int		i;
	
	first_node = map_head;
	last_node = map_head;
	while (last_node->next)
		last_node = last_node->next;
	i = 0;
	while (first_node->line[i] == '1' && last_node->line[i] == '1')
		i++;
	if ((first_node->line[i] != '\0') && (first_node->line[i] != '1'))
		ft_error("Top of map is not surrounded by walls\n");
	if ((last_node->line[i] != '\0') && (last_node->line[i] != '1') && (last_node->line[i] != '\0'))
		ft_error("Bottom of map is not surrounded by walls\n");
}

int		check_map_info(t_info *map_info)
{
	if (map_info->collectibles < 1)
		ft_error("no collectibles (C) found in map\n");
	if (map_info->exits != 1)
		ft_error("1 exit (E) allowed in map\n");
	if (map_info->players != 1)
		ft_error("only 1 player (P) allowed in map\n");
	return (0);
}

void	map_is_valid(t_info *map_info, t_map *map_head)
{
	check_map_info(map_info);
	check_map_side_walls(map_head);
	check_map_top_bottom_walls(map_head);
	map_is_rectangular(map_head);
}