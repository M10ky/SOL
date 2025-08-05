/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokyrakotoarivelo@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:55:39 by miokrako          #+#    #+#             */
/*   Updated: 2025/07/23 18:13:11 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "get_next_line.h"

int	handle_input(int keycode, t_data *data)
{
	if (keycode == 65307)
		exit_game(&data);
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

int is_rectangular(char **map)
{
    int i, j;
    int width;

    i = 0;
    if (!map || !map[0])
        return (0);
    width = 0;
    while (map[0][width])
        width++;
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

int is_surrounded_by_walls(char **map)
{
    int i;
    int width;
    int x;

    i = 0;
    x = 0;
    width = 0;
    while (map[0][width])
        width++;
    while (map[i])
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            return (0);
        i++;
    }
    while (x < width)
    {
        if (map[0][x] != '1' || map[i - 1][x] != '1' )
            return (0);
        x++;
    }
    return (1);
}

int has_required_elements(char **map)
{
    int i = 0, j = 0;
    int p = 0, c = 0, e = 0;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
                p++;
            else if (map[i][j] == 'C')
                c++;
            else if (map[i][j] == 'E')
                e++;
            else if (map[i][j] != '1' && map[i][j] != '0')
                return (0);
            j++;
        }
        i++;
    }
    if (p != 1 || c < 1 || e < 1 || e > 1)
        return (0);
    return (1);
}

int validate_map(char **map)
{
    if (!is_rectangular(map))
    {
        printf("Erreur : carte non rectangulaire\n");
		free_map(map);
		return (0);
    }
    if (!has_required_elements(map))
    {
        printf("Erreur : éléments P/C/E invalides ou caractères inconnus\n");
		free_map(map);
		return (0);
    }
	if (!is_surrounded_by_walls(map))
	{
		printf("Erreur : carte non entourée de murs\n");
		free_map(map);
		return (0);
	}
	if (!is_map_reachable(map))
	{
		printf("Erreur : tous les objets ou la sortie ne sont pas accessibles\n");
		free_map(map);
		return (0);
	}
	return (1);
}

void	find_player(char **map, int *row, int *col)
{
    int i, j;

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
				return;
			}
            j++;
        }
        i++;
    }
}

void	move_player(t_data *data, int drow, int dcol)
{
	int		row, col;
	int		new_r, new_c;
	char	target;

	find_player(data->map, &row, &col);

	new_r = row + drow;
	new_c = col + dcol;
	target = data->map[new_r][new_c];

	if (target == '1')
		return;

	if (target == 'E')
	{
		int remaining = count_collectibles(data);
		if (remaining > 0)
		{
			//printf("🚫 Il reste %d objets à ramasser avant de sortir !\n", remaining);
			return;
		}
		else
		{
			//printf("🎉 Bravo, tu as ramassé tous les objets et atteint la sortie !\n");
		}
	}

	if (target == 'C')
		printf("🧺 Tu as ramassé un objet !\n");

	data->map[row][col] = '0';
	data->map[new_r][new_c] = 'P';

	data->move_count++;
	printf("\r Move : %d    ", data->move_count);
    fflush(stdout);

	render_map(data);
	if (target == 'E')
		exit(0);
}

int count_collectibles(t_data *data)
{
    int count;
    int i;
    int j;

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
char *trim_newline(char *line)
{
	int len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}
char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	dest = malloc(ft_strlen(src) + 1 * sizeof(char));
	i = 0;
	if (dest == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
void	flood_fill(char **map, int row, int col)
{
    if (row < 0 || col < 0)
		return;
    if (map[row] == NULL || map[row][col] == '\0')
		return;
    if (map[row][col] == '1' || map[row][col] == 'V')
		return;
    map[row][col] = 'V';

    flood_fill(map, row + 1, col);
    flood_fill(map, row - 1, col);
    flood_fill(map, row, col + 1);
    flood_fill(map, row, col - 1);
}

int	
check_flood_fill(char **map)
{
	int i = 0, j;

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

int	is_map_reachable(char **map)
{
	char	**map_copy;
	int	row, col;

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
void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_images(t_data *data)
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
}

int	exit_game(t_data **data)
{
	free_map((*data)->map);

	if ((*(data))->img_wall)
		mlx_destroy_image(((*data))->mlx, ((*data))->img_wall);
	if ((*data)->img_floor)
		mlx_destroy_image((*data)->mlx, (*data)->img_floor);
	if ((*data)->img_player)
		mlx_destroy_image((*data)->mlx, (*data)->img_player);
	if ((*data)->img_exit)
		mlx_destroy_image((*data)->mlx, (*data)->img_exit);
	if ((*data)->img_exit_open)
		mlx_destroy_image((*data)->mlx, (*data)->img_exit_open);
	if ((*data)->img_collectible)
		mlx_destroy_image((*data)->mlx, (*data)->img_collectible);
	if ((*data)->win)
	{
		mlx_destroy_window((*data)->mlx, (*data)->win);
		//free((*data)->win);
		free((*data)->mlx);
	}
	exit(0);
	return (0);
}
int	close_window(t_data *data)
{
	exit_game(&data);
	return (0);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1 [i] == s2 [i]) && (s1 [i] != '\0' || s2 [i] != '\0'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	check_map_extension(char *filename)
{
	int	len;

	if (!filename)
		return (0);
	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strcmp(".ber", &filename[len - 4]) == 0)
		return (1);
	return (0);
}
