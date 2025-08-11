/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 11:45:24 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/11 16:02:48 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_input(int keycode, t_data *data)
{
	if (keycode == 65307)
	{
		exit_game(data);
	}
	else if (keycode == 119)
		move_player(data, -1, 0);
	else if (keycode == 115)
		move_player(data, 1, 0);
	else if (keycode == 97)
		move_player(data, 0, -1);
	else if (keycode == 100)
		move_player(data, 0, 1);
	return (0);
}

int	count_collectibles(t_data *data)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	count = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check_map_extension(char *filename)
{
	char	*basename;
	int		len;

	if (!filename)
		return (0);
	basename = ft_strchr(filename, '/');
	if (basename)
		basename++;
	else
		basename = filename;
	len = ft_strlen(basename);
	if (len == 4 && ft_strcmp(basename, ".ber") == 0)
		return (0);
	if (len > 4 && ft_strcmp(".ber", &basename[len - 4]) == 0)
		return (1);
	return (0);
}

void	flood_fill(char **map, int row, int col)
{
	if (row < 0 || col < 0)
		return ;
	if (!map[row] || map[row][col] == '\0')
		return ;
	if (map[row][col] == '1' || map[row][col] == 'V')
		return ;
	map[row][col] = 'V';
	flood_fill(map, row + 1, col);
	flood_fill(map, row - 1, col);
	flood_fill(map, row, col + 1);
	flood_fill(map, row, col - 1);
}

int	check_flood_fill(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
