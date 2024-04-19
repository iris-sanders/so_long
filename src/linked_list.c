/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 18:26:31 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 19:29:26 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*create_node(char *data)
{
	t_map	*node;

	node = malloc(sizeof(t_map));
	if (!node)
		ft_error("failed to create node");
	node->line = ft_strdup(data);
	node->length = line_strlen(data);
	if (node->line[node->length] == '\n')
		node->line[node->length] = '\0';
	node->next = NULL;
	return (node);
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

void	print_list(t_map *head)
{
	t_map	*node;

	node = head;
	while (node != NULL)
	{
		ft_printf("%s", node->line);
		node = node->next;
	}
}

int	count_nodes(t_map *map_head)
{
	t_map	*node;
	int		count;
	
	count = 0;
	node = map_head;
	while (node)
	{
		node = node->next;
		count++;
	}
	return (count);
}