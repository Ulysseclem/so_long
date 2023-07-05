/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:20:00 by ulysse            #+#    #+#             */
/*   Updated: 2023/07/05 11:42:53 by uclement         ###   ########.fr       */
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

#define BUFFER_SIZE 5

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300

#define MLX_ERROR 1

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_textures
{
	t_img floor;
	t_img floor2;
	t_img wall;
	t_img wall2;
	t_img charac;
}	t_textures;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_textures	texture;
	int		cur_img;
}	t_data;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

int main(void);

char	*get_next_line(int fd);
void	to_line(char *stock, char **line);
void	read_stock(char **stock, int fd);
void	free_stock(char **stock);

int		check_newline(char *buf);
char	*gnl_strjoin(char *s1, char *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

void	error_exit(void);
int	render(t_data *data, int x, int y, int i);

void	map_test(t_data data);
char	*ft_strcpy(char *dest, char *src);
void 	map_print(char **map, t_data data, int size);
int		map_size(void);
void	free_map(char **map, int size);

void	map_error(char **map, int y);
void 	map_flood(char **map, int x, int y);
t_pos map_find_start(char **map, int size);
int	map_flood_check(char **map, int size);


#endif
