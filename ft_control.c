/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 15:28:27 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/11 21:52:52 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(char **map, int *row, int *col)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*row = i;
				*col = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

char	**copy_map(char **map)
{
	int		count;
	int		i;
	char	**map_copy;

	i = 0;
	count = 0;
	while (map[count])
		count++;
	map_copy = malloc(sizeof(char *) * (count + 1));
	if (!map_copy)
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
	return (map_copy);
}

void	render_map(t_data *d)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (d->map[i])
	{
		j = 0;
		while (d->map[i][j])
		{
			x = j * TILE_SIZE;
			y = i * TILE_SIZE;
			draw_tile(d, d->map[i][j], x, y);
			j++;
		}
		i++;
	}
}

void	print_move_count(int count)
{
	char	*count_str;

	count_str = ft_itoa(count);
	if (!count_str)
		return ;
	ft_putstr_fd("\rMove : ", 1);
	ft_putstr_fd(count_str, 1);
	ft_putstr_fd("    ", 1);
	free(count_str);
}

void	move_player(t_data *data, int drow, int dcol)
{
	int		row;
	int		col;
	int		new_r;
	int		new_c;
	char	target;

	find_player(data->map, &row, &col);
	new_r = row + drow;
	new_c = col + dcol;
	target = data->map[new_r][new_c];
	if (target == '1')
		return ;
	if (target == 'E' && count_collectibles(data) == 0)
		exit_game(data);
	else if (target == 'E')
		return ;
	data->map[row][col] = '0';
	data->map[new_r][new_c] = 'P';
	data->move_count++;
	print_move_count(data->move_count);
	render_map(data);
}
