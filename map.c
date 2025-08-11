/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 12:35:12 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/11 22:56:21 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	open_map_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error : No such file\n", 21);
		return (-1);
	}
	return (fd);
}

static char	**append_line(char **map, char *line, int count)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		return (free_map(map), NULL);
	i = 0;
	while (i < count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[count] = line;
	new_map[count + 1] = NULL;
	free(map);
	return (new_map);
}

static char	*process_line(char *line)
{
	char	*trimmed;

	trimmed = trim_newline(line);
	if (trimmed[0] == '\0')
	{
		free(trimmed);
		return (NULL);
	}
	return (trimmed);
}

char	**read_map(const char *filename)
{
	int		fd;
	char	**map;
	char	*line;
	int		count;

	fd = open_map_file(filename);
	if (fd < 0)
		return (NULL);
	map = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = process_line(line);
		if (line)
		{
			map = append_line(map, line, count++);
			if (!map)
				return (NULL);
		}
		line = get_next_line(fd);
	}
	close(fd);
	get_next_line(-1);
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
