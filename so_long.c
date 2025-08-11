/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:19:09 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/11 22:14:01 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	return (0);
}

static int	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		write(2, "Invalid Argument\n", 17);
		return (0);
	}
	if (!check_map_extension(av[1]))
	{
		write(2, "Invalid Map Extension\n", 22);
		return (0);
	}
	return (1);
}

static int	load_map(t_data *data, char *filename)
{
	data->map = read_map(filename);
	if (!data->map)
	{
		write(2, "Map Error\n", 10);
		return (0);
	}
	if (!validate_map(data->map))
		return (0);
	return (1);
}

static int	init_window(t_data *data)
{
	int	win_width;
	int	win_height;

	win_width = 0;
	win_height = 0;
	while (data->map[0][win_width])
		win_width++;
	while (data->map[win_height])
		win_height++;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (print_error("Error init MLX\n"));
	data->win = mlx_new_window(
			data->mlx,
			win_width * TILE_SIZE,
			win_height * TILE_SIZE,
			"so_long");
	return (data->win != NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	if (!check_args(argc, argv) || !load_map(&data, argv[1]))
		return (1);
	if (!init_window(&data))
		return (1);
	load_images(&data);
	render_map(&data);
	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 0, exit_game, &data);
	mlx_loop(data.mlx);
	return (0);
}
