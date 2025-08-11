/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_and_free.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:41:11 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/11 21:49:58 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	*load_image_or_exit(t_data *data, char *path)
{
	int		w;
	int		h;
	void	*img;

	img = mlx_xpm_file_to_image(data->mlx, path, &w, &h);
	if (!img)
	{
		write(2, "Error\nFailed to load image: ", 28);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		exit_game(data);
		exit(1);
	}
	return (img);
}

void	load_images(t_data *data)
{
	data->img_wall = load_image_or_exit(data, "textures/final_wall.xpm");
	data->img_floor = load_image_or_exit(data, "textures/floor.xpm");
	data->img_player = load_image_or_exit(data, "textures/fplayer.xpm");
	data->img_exit = load_image_or_exit(data, "textures/close.xpm");
	data->img_exit_open = load_image_or_exit(data, "textures/open.xpm");
	data->img_collectible = load_image_or_exit(data, "textures/Collect.xpm");
}

void	destroy_images(t_data *data)
{
	if (!data)
		return ;
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_floor)
		mlx_destroy_image(data->mlx, data->img_floor);
	if (data->img_player)
		mlx_destroy_image(data->mlx, data->img_player);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
	if (data->img_exit_open)
		mlx_destroy_image(data->mlx, data->img_exit_open);
	if (data->img_collectible)
		mlx_destroy_image(data->mlx, data->img_collectible);
}

int	exit_game(t_data *data)
{
	if (data->img_wall)
		mlx_destroy_image(data->mlx, data->img_wall);
	if (data->img_floor)
		mlx_destroy_image(data->mlx, data->img_floor);
	if (data->img_player)
		mlx_destroy_image(data->mlx, data->img_player);
	if (data->img_exit)
		mlx_destroy_image(data->mlx, data->img_exit);
	if (data->img_exit_open)
		mlx_destroy_image(data->mlx, data->img_exit_open);
	if (data->img_collectible)
		mlx_destroy_image(data->mlx, data->img_collectible);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	if (data->map)
		free_map(data->map);
	free(data->mlx);
	exit(0);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
