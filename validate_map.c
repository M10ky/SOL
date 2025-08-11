/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:38:13 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/11 22:32:54 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_rectangular(char **map)
{
	int	i;
	int	j;
	int	width;

	if (!map || !map[0])
		return (0);
	width = 0;
	while (map[0][width])
		width++;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (j != width)
			return (0);
		i++;
	}
	return (1);
}

int	is_surrounded_by_walls(char **map)
{
	int	i;
	int	width;
	int	x;

	width = 0;
	while (map[0][width])
		width++;
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
		i++;
	}
	x = 0;
	while (x < width)
	{
		if (map[0][x] != '1' || map[i - 1][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	has_required_elements(char **map)
{
	int	p;
	int	c;
	int	e;

	p = 0;
	c = 0;
	e = 0;
	count_elements(map, &p, &c, &e);
	if (p != 1 || c < 1 || e != 1)
		return (0);
	return (1);
}

int	is_map_reachable(char **map)
{
	char	**map_copy;
	int		row;
	int		col;

	map_copy = copy_map(map);
	if (!map_copy)
		return (0);
	find_player(map_copy, &row, &col);
	flood_fill(map_copy, row, col);
	if (check_flood_fill(map_copy))
	{
		free_map(map_copy);
		return (0);
	}
	free_map(map_copy);
	return (1);
}

int	validate_map(char **map)
{
	if (!is_rectangular(map))
	{
		write(2, "Map is not rectangular\n", 23);
		free_map(map);
		return (0);
	}
	if (!has_required_elements(map))
	{
		write(2, "Map Error : invalid P/C/E\n", 26);
		free_map(map);
		return (0);
	}
	if (!is_surrounded_by_walls(map))
	{
		write(2, "Map Error : wall\n", 17);
		free_map(map);
		return (0);
	}
	if (!is_map_reachable(map))
	{
		write(2, "Map Error : no access to all collectibles\n", 42);
		free_map(map);
		return (0);
	}
	return (1);
}
