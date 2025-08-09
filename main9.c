/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:19:09 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/09 22:40:14 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <errno.h>

int	main(int ac, char **av)
{
	t_data	data = {0};
	int		win_width = 0;
	int		win_height = 0;
	int i = 0;

	data.move_count = 0;
	data.map = NULL;

	// Gestion des arguments
	if (ac != 2)
	{
		// errno = (ac < 2) ? EINVAL : E2BIG;
		// printf("Error \n%s\n", strerror(errno));
		write(2,"Invalid Argument\n",17);
		return (1);
	}
	else if (!check_map_extension(av[1]))
	{
		//fprintf(stderr, "Erreur : le fichier doit avoir l'extension .ber\n");
		write(2,"Invalid Map Extension\n",22);
		return (1);
	}

		// Lecture de la carte avec get_next_line
	data.map = read_map(av[1]);
	if (!data.map)
	{
		free(data.map);
		return(0);
	}
	while (data.map[i])
	{
		printf("%s\n", data.map[i]);
		i++;
	}
	if (!data.map)
	{
		perror("Erreur lecture carte");
		free(data.map);
		return (1);
	}

	// Validation de la carte
	if (!validate_map(data.map))
		return (1);

	// Initialisation fenêtre
	data.mlx = mlx_init();
	if (!data.mlx)
	{
		write(2, "Error init MLX\n",15);
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
