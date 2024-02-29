/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:56:41 by irsander          #+#    #+#             */
/*   Updated: 2024/02/29 19:54:48 by irsander         ###   ########.fr       */
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

static void	ft_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
static size_t	line_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}
static void	init_map_info(t_info *map_info)
{
	map_info->empty_spaces = 0;
	map_info->walls = 0;
	map_info->collectibles = 0;
	map_info->exits = 0;
	map_info->players = 0;
	map_info->newlines = 0;
	map_info->endlines = 0;
}

static void map_info_counter(t_map *map_head, t_info *map_info)
{
	int		i;
	t_map	*node;
	
	node = map_head;
	while (node->next)
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

void	validate_map(t_map *map_head, t_info *map_info)
{
	t_map	*node;
	
	node = map_head;
	init_map_info(map_info); //map_info = (t_info){0};
	map_info_counter(map_head, map_info); //maaybe put this in struct map + make libft better by adding gnl and the bonus
	while (node->next) //make new function out of this part it returns int
	{
		if (!(node->length == node->next->length))
			ft_error("map is not rectangular");
		node = node->next;	
	}
	printf("node is rectangular");
	
	//rectangular >> strlen every node same? return 0 otherwise exit
	//must be surrounded by walls >> first and last nodes only 1 other nodes first and last 1
	//count E (exit) must be 1
	//count C (collectible) must be > 0
	//count P (player) must be 1
	// if theres any other character then 0 1 C E P /n /0 en geen /0 +1 map is invalid
}

void	node_add_back(t_map **head, t_map *new_node)
{
	t_map	*node;

	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	node = *head;
	while (node->next)
		node = node->next;
	node->next = new_node;
}

t_map	*create_node(char *data)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		ft_error("failed to create node");
	node->line = ft_strdup(data);
	node->length = line_strlen(data);
	printf("length: %i", node->length);
	node->next = NULL;
	return (node);
}

static void	print_list(t_map *head)
{
	t_map	*node;

	node = head;
	while (node != NULL)
	{
		ft_printf("%s", node->line);
		node = node->next;
	}
	ft_printf("\n");
}

t_map	*open_file(char *file)
{
	int		fd;
	char	*line;
	t_map	*head;
	t_map	*new_node;

	head = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("unable to open map");
	line = get_next_line_gnl(fd);
	// if (!line)
	//error free line
	while (line != NULL)
	{
		new_node = create_node(line);
		node_add_back(&head, new_node);
		line = get_next_line_gnl(fd);
	}
	print_list(head);
	close(fd);
	return (head);
}

t_map	*map_init(char *file, t_info *map_info)
{
	t_map	*map_head;
	
	map_head = open_file(file);
	validate_map(map_head, map_info);
	// if (!validate_map(map_head))
		//error
	return (map_head);
}
