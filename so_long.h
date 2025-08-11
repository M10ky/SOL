/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:21:50 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/11 22:40:26 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stddef.h>
# include "ft_printf/ft_printf.h"
# include "mlx/mlx.h"

# define TILE_SIZE 64
# define BUFFER_SIZE 42

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_floor;
	void	*img_player;
	void	*img_exit;
	void	*img_exit_open;
	void	*img_collectible;
	char	**map;
	int		move_count;
}	t_data;

size_t	ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
void	*ft_calloc(size_t n, size_t size);
char	*trim_newline(char *line);
char	*ft_strdup(const char *src);
char	**copy_map(char **map);
char	**read_map(const char *filename);
void	ft_bzero(void *s, size_t n);
int		validate_map(char **map);
void	load_images(t_data *data);
int		is_surrounded_by_walls(char **map);
int		is_map_reachable(char **map);
int		handle_input(int keycode, t_data *data);
int		is_rectangular(char **map);
int		has_required_elements(char **map);
void	render_map(t_data *d);
void	move_player(t_data *data, int drow, int dcol);
void	find_player(char **map, int *row, int *col);
int		check_flood_fill(char **map);
int		count_collectibles(t_data *data);
void	draw_tile(t_data *d, char c, int x, int y);
void	flood_fill(char **map, int row, int col);
void	free_map(char **map);
void	destroy_images(t_data *data);
int		exit_game(t_data *data);
int		check_map_extension(char *filename);
int		ft_strcmp(char *s1, char *s2);
void	print_move_count(int count);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
void	count_elements(char **map, int *p, int *c, int *e);

#endif
