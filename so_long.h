/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miokrako <miokrako@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:21:50 by miokrako          #+#    #+#             */
/*   Updated: 2025/08/09 17:36:05 by miokrako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// ----- Includes communs -----
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <errno.h>
# include "mlx/mlx.h"

// ----- Constantes -----
# define TILE_SIZE 96
# define BUFFER_SIZE 42

// ----- Structures -----
typedef struct s_data {
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

// ----- Prototypes get_next_line -----
char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t n, size_t size);

// ----- Prototypes so_long -----
int		validate_map(char **map);
char	**copy_map(char **map);
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
char	**read_map(const char *filename);
int		count_collectibles(t_data *data);
void	draw_tile(t_data *d, char c, int x, int y);
char	*trim_newline(char *line);
char	*ft_strdup(const char *src);
void	flood_fill(char **map, int row, int col);
void	free_map(char **map);
void	destroy_images(t_data *data);
int		exit_game(t_data **data);
int		close_window(t_data *data);
int		check_map_extension(char *filename);

#endif

