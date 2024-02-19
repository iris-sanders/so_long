/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:56:41 by irsander          #+#    #+#             */
/*   Updated: 2024/02/19 19:06:29 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// map has 3 components: walls, collectibles, free space
// 0 = empty space
// 1 = wall
// C = collectible
// E = map exit
// P = Players starting position

// MUST contain to be valid: 1 exit, 1 collectible, 1 starting position
// rectangular map
// MUST be surrounded by walls, if not return error. ("Error\n") followed by 
// explicit error message
// check if theres a valid path
#include "so_long.h"

void	ft_error(void)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	read_map(void)
{
	int		map_y;
	int		fd;
	char	**map;

	*map = NULL;
	fd = open("map.ber", O_RDONLY);
	if (fd == -1)
	{
		ft_error();
		ft_printf("unable to open map");
	}
	map_y = 0;
	map[map_y] = get_next_line(fd);
	while (map[map_y] != NULL)
	{
		map_y++;
		map[map_y] = get_next_line(fd);
	}
}