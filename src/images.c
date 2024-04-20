/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:52:21 by irsander          #+#    #+#             */
/*   Updated: 2024/04/19 20:27:45 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_player_image(mlx_t *mlx, t_images *images)
{
	images->p_texture = mlx_load_png("textures/fox.png");
	if (!images->p_texture)
		ft_error("failed to load player png");
	images->p_image = mlx_texture_to_image(mlx, images->p_texture);
	if (!images->p_image)
		ft_error("failed to create player image");
}

void	get_background_image(mlx_t *mlx, t_images *images)
{
	images->b_texture = mlx_load_png("textures/background.png");
	if (!images->b_texture)
		ft_error ("failed to load background png");
	images->b_image = mlx_texture_to_image(mlx, images->b_texture);
	if (!images->b_image)
		ft_error("failed to create background image");
}

void	get_wall_image(mlx_t *mlx, t_images *images)
{
	images->w_texture = mlx_load_png("textures/tree.png");
	if (!images->w_texture)
		ft_error ("failed to load wall png");
	images->w_image = mlx_texture_to_image(mlx, images->w_texture);
	if (!images->w_image)
		ft_error("failed to create wall image");
}

void	get_collectible_image(mlx_t *mlx, t_images *images)
{
	images->c_texture = mlx_load_png("textures/flower.png");
	if (!images->c_texture)
		ft_error ("failed to load collectible png");
	images->c_image = mlx_texture_to_image(mlx, images->c_texture);
	if (!images->c_image)
		ft_error("failed to create collectible image");
}

void	get_exit_image(mlx_t *mlx, t_images *images)
{
	images->e_texture = mlx_load_png("textures/portal.png");
	if (!images->e_texture)
		ft_error ("failed to load exit png");
	images->e_image = mlx_texture_to_image(mlx, images->e_texture);
	if (!images->e_image)
		ft_error("failed to create exit image");
}
