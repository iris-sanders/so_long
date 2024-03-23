/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:52:18 by irsander          #+#    #+#             */
/*   Updated: 2024/03/23 18:19:05 by irsander         ###   ########.fr       */
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
	node->length = line_strlen(data); //add the collectib les and stuff here and make 1 validate function
	if (node->line[node->length] == '\n')
		node->line[node->length] = '\0';
	// printf("length: %i", node->length);
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

size_t	line_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
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
	ft_printf("\n");
}

void	ft_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}


