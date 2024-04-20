/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irsander <irsander@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 15:17:37 by irsander          #+#    #+#             */
/*   Updated: 2024/04/20 17:00:42 by irsander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int32_t	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_info		map_info;
	char		**array;
	t_all		all_info;

	if (argc != 2)
	{
		ft_putstr_fd("Error: invalid numer of arguments\n", STDERR_FILENO);
		ft_putstr_fd("<name_of_program> <path_to_map_file>\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	array = parse_map(argv[1], &map_info);
	calc_tilesize(&map_info);
	mlx = mlx_init(map_info.x_length * map_info.im.tile_size, \
			map_info.y_length * map_info.im.tile_size, "MLX42", false);
	if (!mlx)
		ft_error_mlx(mlx);
	load_png(mlx, &map_info.im);
	all_info = (t_all){&map_info, mlx, array, &map_info.im};
	render_map(&all_info);
	mlx_key_hook(mlx, &ft_keyhook, &all_info);
	mlx_loop(mlx);
	ft_printf("\n");
	cleanup(&all_info, array);
	return (EXIT_SUCCESS);
}
