/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:17:37 by irsander          #+#    #+#             */
/*   Updated: 2024/03/22 16:24:40 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//to do: 
// 1. Calculate the appropriate size for each tile based on te dimensions of the game window and size of the map
// 2. Load PNG images for P (player), W (walls), C (collectibles), 0 (empty spaces (background))
//    - use the functions load png, texture to image, image to window
// 3. Iterate through the 2d map array and assign the correct images to each tile based on the characters.
// 4. Determine the screen coordinates for each tile based on its position in the map array and the calculated tile size
//    Render each tile at its calculated position on the screen.
// 5. Implement logic to allow player movement based on user input (W, A, S, D)
//    -Update player position in the 2d map array and adjust rendering accordingly.
// 6. Render the map with updated textures and positions
// 7. Implement functionality for collecting collectibles
//    - remove collectible from the map and decrement collectible count when collected by the player
//    - check for game completion when all collectibles are collected and player reached the exit
// 8. Make sure the player isnt able to walk into walls
// 9. At every move, the current number of movements must be displayed in the shell 




#include "so_long.h"

static void ft_error_mlx(mlx_t *mlx)
{
	if (mlx)
		mlx_close_window(mlx);
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	mlx_t *mlx = param;
	(void)mlx;

	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(255, 231, 29, 205);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_info		map_info;
	t_player	player_info;
	char		**array;

	if (argc != 2)
	{
		ft_putstr_fd("Error: invalid numer of arguments\n", STDERR_FILENO);
		ft_putstr_fd("<name_of_program> <path_to_map_file>\n", STDERR_FILENO); //What is stder_fileno // why to use it
		exit(EXIT_FAILURE);
	}
	array = parse_map(argv[1], &map_info, &player_info);
	
	// printf("collectibles: %i\n", map_info.collectibles);
	(void) array;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
		ft_error_mlx(mlx);
	if (!(image = mlx_new_image(mlx, 128, 128)))
		ft_error_mlx(mlx);
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
		ft_error_mlx(mlx);
	
	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

