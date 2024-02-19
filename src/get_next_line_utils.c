/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 16:44:43 by irsander          #+#    #+#             */
/*   Updated: 2024/02/19 19:18:19 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/so_long.h"

void	*ft_free_gnl(char **s)
{
	free(*s);
	*s = NULL;
	return (NULL);
}

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strchr_gnl(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	if (!s[i])
		return (-1);
	return (i);
}

char	*ft_strcat_gnl(char *s, char *buf)
{
	int				i;
	int				j;
	char			*temp;

	i = 0;
	j = 0;
	temp = malloc((ft_strlen_gnl(s) + ft_strlen_gnl(buf) +1) * sizeof(char));
	if (!temp)
		return (ft_free_gnl(&s));
	while (s[i])
		temp[j++] = s[i++];
	i = 0;
	while (buf[i])
		temp[j++] = buf[i++];
	temp[j] = '\0';
	free(s);
	s = temp;
	return (s);
}