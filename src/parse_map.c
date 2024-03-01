/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:56:41 by irsander          #+#    #+#             */
/*   Updated: 2024/03/01 19:49:24 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// map has 3 components: walls, collectibles, free space
// 0 = empty space
// 1 = wall
// C = collectible
// E = map exit
// P = Players starting position

// while node>next niet goed (1 line doesnt work)
// 
// MUST contain to be valid: 1 exit, 1 collectible, 1 starting position
// rectangular map
// MUST be surrounded by walls, if not return error. ("Error\n") followed by 
// explicit error message
// check if theres a valid path
#include "so_long.h"


static void init_map_info(t_map *map_head, t_info *map_info)
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
			if (node->line[i] == '0')
				map_info->empty_spaces += 1;
			else if (node->line[i] == '1')
				map_info->walls += 1;
			else if (node->line[i] == 'C')
				map_info->collectibles += 1;
			else if (node->line[i] == 'E')
				map_info->exits += 1;
			else if (node->line[i] == 'P')
				map_info->players += 1;
			else if (node->line[i] == '\n')
				map_info->newlines += 1;
			else if (node->line[i] == '\0')
				map_info->endlines += 1;
			else
				ft_error("unvalid map, allowed characters: 0,1,C,E,P");
			i++;
		}
		node = node->next;
	}
}

static int	map_is_rectangular(t_map *map_head)
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

static int	map_has_walls(t_map *map_head)
{
	t_map	*node;
	t_map	*first_node;
	t_map	*last_node;
	int		i;
	
	node = map_head;
	while (node)
	{
		i = node->length -1;
		if ((node->line[0] != '1') || (node->line[i] != '1'))
			ft_error("side of map not surrounded by wall");
		node = node->next;
	}
	first_node = map_head;
	last_node = map_head;
	while (last_node->next)
		last_node = last_node->next;
	i = 0;
	while (first_node->line[i] == '1' && last_node->line[i] == '1')
		i++;
	if ((first_node->line[i] != '\n') && (first_node->line[i] != '1'))
		ft_error("Top of map is not surrounded by walls\n");
	if ((last_node->line[i] != '\n') && (last_node->line[i] != '1') && (last_node->line[i] != '\0'))
		ft_error("Bottom of map is not surrounded by walls\n");
	return (0);
}
static int	validate_info(t_info *map_info)
{
	if (map_info->collectibles < 1)
		ft_error("no collectibles (C) found in map\n");
	if (map_info->exits != 1)
		ft_error("only 1 exit (E) allowed in map\n");
	if (map_info->players != 1)
		ft_error("only 1 player (P) allowed in map\n");
	return (0);
}

t_map	*open_map(char *file)
{
	int		fd;
	char	*line;
	t_map	*head;
	t_map	*new_node;

	head = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("unable to open map");
	if (read(fd, 0, 0) == -1)
		ft_error("unable to read map");
	line = get_next_line_gnl(fd);
	// if (!line)
	//error free line
	while (line != NULL)
	{
		new_node = create_node(line);
		node_add_back(&head, new_node);
		line = get_next_line_gnl(fd);
	}
	// print_list(head);
	close(fd);
	return (head);
}

t_map	*parse_map(char *file, t_info *map_info)
{
	t_map	*map_head;
	
	map_head = open_map(file);
	if (!map_head)
		ft_error("failed to open map\n");
	init_map_info(map_head, map_info);
	validate_info(map_info); 
	map_is_rectangular(map_head);
	map_has_walls(map_head);
	// map_exit_is_reachable()

	
	return (map_head);
}
