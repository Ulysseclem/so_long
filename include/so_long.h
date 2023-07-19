/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:20:34 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 17:25:41 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <X11/keysym.h>
# include <stdlib.h>
# include <X11/X.h>
# include <fcntl.h>
# include <unistd.h>
# include <inttypes.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

# define BUFFER_SIZE 5
# define MLX_ERROR 1

# define XPM_IMG_COUNT	24
# define WALL			"xpm/wall/all.xpm"
# define WALL_TOP		"xpm/wall/top.xpm"
# define FLOOR			"xpm/floor/dirt_1.xpm"
# define FLOOR_H		"xpm/floor/half.xpm"
# define CHARAC			"xpm/charac/floor.xpm"
# define CHARAC_L		"xpm/charac/floor_left.xpm"
# define CHARAC_H		"xpm/charac/floor_half.xpm"
# define CHARAC_H_L		"xpm/charac/floor_half_left.xpm"
# define CHARAC_TOP		"xpm/charac/floor_head.xpm"
# define CHARAC_TOP_L	"xpm/charac/floor_head_left.xpm"
# define CHARAC_TOP_W	"xpm/charac/top_wall.xpm"
# define CHARAC_TOP_W_L	"xpm/charac/top_wall_left.xpm"
# define DIAMOND		"xpm/diamond/floor.xpm"
# define DIAMOND_H		"xpm/diamond/floor_half.xpm"
# define DIAMOND_C		"xpm/diamond/charac.xpm"
# define DIAMOND_C_L	"xpm/diamond/charac_left.xpm"
# define EXIT			"xpm/exit/exit.xpm"
# define EXIT_H			"xpm/exit/half.xpm"
# define EXIT_C			"xpm/exit/charac.xpm"
# define EXIT_C_L		"xpm/exit/charac_left.xpm"
# define EXIT_LCK		"xpm/exit/lock.xpm"
# define EXIT_LCK_H		"xpm/exit/lock_half.xpm"
# define EXIT_LCK_C		"xpm/exit/lock_charac.xpm"
# define EXIT_LCK_C_L	"xpm/exit/lock_charac_left.xpm"

typedef struct s_map
{
	char	**map;
	int		x;
	int		y;
	int		start_x;
	int		start_y;
	int		nbr_e;
	int		nbr_p;
	int		nbr_c;
	int		px_x;
	int		px_y;
	int		start;
	int		count_move;
	char	*map_name;
}	t_map;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			height;
	int			width;
}	t_img;

typedef struct s_textures
{
	t_img	wall_all;
	t_img	wall_top;

	t_img	floor_dirt_1;
	t_img	floor_half;

	t_img	charac_floor;
	t_img	charac_floor_half;
	t_img	charac_floor_head;
	t_img	charac_top_wall;

	t_img	charac_floor_left;
	t_img	charac_floor_half_left;
	t_img	charac_floor_head_left;
	t_img	charac_top_wall_left;

	t_img	diamond_floor;
	t_img	diamond_floor_half;
	t_img	diamond_floor_charac;
	t_img	diamond_floor_charac_left;

	t_img	exit;
	t_img	exit_half;
	t_img	exit_charac;
	t_img	exit_charac_left;

	t_img	exit_lock;
	t_img	exit_lock_half;
	t_img	exit_lock_charac;
	t_img	exit_lock_charac_left;

	t_img	*tab;
	int		count;
	int		height;
	int		width;
}	t_textures;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_textures	texture;
}	t_game;

int		check_file(int ac, char *av);

void	map_read(t_game *game);
void	map_size(t_map *map);
char	**map_cpy(t_map *map, char **mappy);
void	map_find_start(t_map *map);
void	map_find_diamond(t_map *map);

void	load_asset(t_textures *texture, void *mlx, t_game *game);
int		render(t_game *game, int x, int y, void *img);
t_img	init_image(void *mlx, char *path, t_game *game);

void	map_error(t_map *map);
void	map_error_tiles(char tile, t_map *map);
void	map_is_possible(t_map *map);
void	map_flood(char **map, int x, int y);
int		map_flood_check(char **map, int size);

int		map_print(t_game *data);
void	print_floor_wall_diamond(t_game *game, t_map *map, int i, int j);
void	print_exit(t_game *game, t_map *map, int i, int j);
void	print_charac(t_game *game, t_map *map, int i, int j);
void	print_charac_left(t_game *game, t_map *map, int i, int j);

int		handle_input(int key, t_game *game);
void	move_right(t_map *map, t_game *game);
void	move_left(t_map *map, t_game *game);
void	move_up(t_map *map, t_game *game);
void	move_dowm(t_map *map, t_game *game);

void	error_exit(char *str);
void	error_exit_free_map(char *str, t_map *map);
int		handle_keypress(int key, t_game *game);
void	free_assets(void *ptr, t_textures *texture);
void	end(t_game *game);

int		ft_printf(const char *str, ...);
int		ft_putchar(char c);
int		ft_putnbr(long int i);
int		ft_which(const char *str, va_list args);

char	*get_next_line(int fd);
void	to_line(char *stock, char **line);
void	read_stock(char **stock, int fd);
void	free_stock(char **stock);

int		check_newline(char *buf);
char	*gnl_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

char	*ft_strcpy(char *dest, char *src);
void	free_map(char **map, int size);
void	map_init(t_game *game);
void	check_images_exist(void);
char	*get_xpm_filename(int i);

#endif