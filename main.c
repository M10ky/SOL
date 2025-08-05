/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokyrakotoarivelo@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:19:09 by miokrako          #+#    #+#             */
/*   Updated: 2025/07/23 17:37:09 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	t_data	data;
	int		win_width = 0;
	int		win_height = 0;
	int i = 0;

	data.move_count = 0;
	data.map = NULL;

	// Gestion des arguments
	if (ac != 2)
	{
		errno = (ac < 2) ? EINVAL : E2BIG;
		printf("Error \n%s\n", strerror(errno));
		return (1);
	}
	else if (!check_map_extension(av[1]))
	{
		fprintf(stderr, "Erreur : le fichier doit avoir l'extension .ber\n");
		return (1);
	}

		// Lecture de la carte avec get_next_line
	data.map = read_map(av[1]);
	if (!data.map)
		return(0);
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	if (!data.map)
	{
		perror("Erreur lecture carte");
		return (1);
	}

	// Validation de la carte
	if (!validate_map(data.map))
	{
		fprintf(stderr, "Map Error\n");
		return (1);
	}

	// Initialisation fenêtre
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		fprintf(stderr, "Erreur initialisation MLX\n");
		return (1);
	}

	while (data.map[0][win_width])
		win_width++;
	while (data.map[win_height])
		win_height++;

	data.win = mlx_new_window(data.mlx, win_width * TILE_SIZE, win_height * TILE_SIZE, "so_long");

	load_images(&data);
	render_map(&data);
	mlx_key_hook(data.win, handle_input, &data);
	mlx_hook(data.win, 17, 0, exit_game, &data);
	mlx_loop(data.mlx);

	return (0);
}
