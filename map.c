/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokyrakotoarivelo@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:35:12 by miokrako          #+#    #+#             */
/*   Updated: 2025/07/23 17:42:03 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"
#include "get_next_line.h"
#include "mlx/mlx.h"

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1024

// char	**read_map(const char *filename)
// {
// 	int		fd;
// 	char	**map;
// 	char	buffer[MAX_LINE_LENGTH];
// 	int		i = 0;
// 	char	c;
// 	int		pos;

// 	map = malloc(sizeof(char *) * (MAX_LINES + 1));
// 	if (!map)
// 		return (NULL);
// 	fd = open(filename, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);

// 	while (1)
// 	{
// 		pos = 0;
// 		while (read(fd, &c, 1) > 0 && c != '\n')
// 			buffer[pos++] = c;
// 		buffer[pos] = '\0';

// 		if (pos == 0 && c != '1')
// 			break;

// 		map[i] = malloc(pos + 1);
// 		if (!map[i])
// 			return (NULL);

// 		// while (j <= pos)
// 		// {
// 		// 	map[i][j] = buffer[j];
// 		// 	j++;
// 		// }

// 		for (int j = 0; j <= pos; j++)
// 			map[i][j] = buffer[j];
// 		i++;

// 		if (c == 0 || pos == 0)
// 			break;
// 	}
// 	map[i] = NULL;
// 	close(fd);
// 	return (map);
// }

char **read_map(const char *filename)
{
	int		fd;
	char	*line;
	char	**map = NULL;
	int		lines = 0;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\n");
		return (NULL);
	}
	while ((line = get_next_line(fd)))
	{
		lines++;
		free(line);
	}
	close(fd);
	map = malloc(sizeof(char *) * (lines + 1));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Erreur à la réouverture");
		return (NULL);
	}
	int i = 0;
	while (i < lines && (line = get_next_line(fd)))
	{
		map[i] = trim_newline(line);
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}


void	draw_tile(t_data *d, char c, int x, int y)
{
	if (c == '1')
		mlx_put_image_to_window(d->mlx, d->win, d->img_wall, x, y);
	else if (c == '0')
		mlx_put_image_to_window(d->mlx, d->win, d->img_floor, x, y);
	else if (c == 'P')
		mlx_put_image_to_window(d->mlx, d->win, d->img_player, x, y);
	else if (c == 'C')
		mlx_put_image_to_window(d->mlx, d->win, d->img_collectible, x, y);
	else if (c == 'E')
	{
		if (count_collectibles(d) == 0)
			mlx_put_image_to_window(d->mlx, d->win, d->img_exit_open, x, y);
		else
			mlx_put_image_to_window(d->mlx, d->win, d->img_exit, x, y);
	}
}


void	render_map(t_data *d)
{
	int	i;
	int	j;

	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			int x = j * TILE_SIZE;
			int y = i * TILE_SIZE;
			draw_tile(d, d->map[i][j], x, y);
			j++;
		}
		i++;
	}
}
void	load_images(t_data *data)
{
	int	w;
	int	h;

	data->img_wall = mlx_xpm_file_to_image(data->mlx, "textures/final_wall.xpm", &w, &h);
	data->img_floor = mlx_xpm_file_to_image(data->mlx, "textures/floor.xpm", &w, &h);
	data->img_player = mlx_xpm_file_to_image(data->mlx, "textures/fplayer.xpm", &w, &h);
	data->img_exit = mlx_xpm_file_to_image(data->mlx, "textures/close.xpm", &w, &h);
	data->img_exit_open = mlx_xpm_file_to_image(data->mlx, "textures/open.xpm", &w, &h);
	data->img_collectible = mlx_xpm_file_to_image(data->mlx, "textures/Collect.xpm", &w, &h);
}

char	**copy_map(char **map)
{
	int	count;
	int	i;
	char **map_copy;

	i = 0;
	count = 0;
	while (map[count])
		count++;
	map_copy = malloc(sizeof(char *) * (count + 1));
	if(!map_copy)
		return (NULL);
	while (i < count)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
		{
			free_map(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return(map_copy);
}
