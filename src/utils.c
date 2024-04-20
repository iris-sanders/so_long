/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:52:18 by irsander          #+#    #+#             */
/*   Updated: 2024/04/20 17:33:27 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	line_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

void	free_2d_array(char **array)
{
	int	y;

	y = 0;
	while (array[y] != NULL)
	{
		free(array[y]);
		y++;
	}
	free(array);
}

void	ft_error(char *msg)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	cleanup(t_all *all_info, char **array)
{
	mlx_delete_texture(all_info->imgs->p_texture);
	mlx_delete_texture(all_info->imgs->b_texture);
	mlx_delete_texture(all_info->imgs->w_texture);
	mlx_delete_texture(all_info->imgs->c_texture);
	mlx_delete_texture(all_info->imgs->e_texture);
	mlx_delete_image(all_info->mlx, all_info->imgs->b_image);
	mlx_delete_image(all_info->mlx, all_info->imgs->c_image);
	mlx_delete_image(all_info->mlx, all_info->imgs->e_image);
	mlx_delete_image(all_info->mlx, all_info->imgs->p_image);
	mlx_delete_image(all_info->mlx, all_info->imgs->w_image);
	free_2d_array(array);
	mlx_terminate(all_info->mlx);
}

void	ft_error_mlx(mlx_t *mlx)
{
	if (mlx)
		mlx_close_window(mlx);
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}
