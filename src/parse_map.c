/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:56:41 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 20:27:59 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (!line)
		ft_error("couldn't get the next line\n");
	while (line != NULL)
	{
		new_node = create_node(line);
		free(line);
		node_add_back(&head, new_node);
		line = get_next_line_gnl(fd);
	}
	close(fd);
	return (head);
}

char	**parse_map(char *file, t_info *map_info)
{
	t_map	*map_head;
	char	**array;

	array = NULL;
	map_head = open_map(file);
	if (!map_head)
		ft_error("failed to open map\n");
	init_map_info(map_head, map_info);
	map_is_valid(map_info, map_head);
	array = path_is_valid(map_head, map_info, array);
	return (array);
}
