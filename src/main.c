/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:21:45 by ulysse            #+#    #+#             */
/*   Updated: 2023/07/06 11:48:42 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>


void	error_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit (0);
}
void	error_exit_free_map(char *str, t_map *map)
{
	free_map(map->map, map->y);
	write(2, str, ft_strlen(str));
	exit (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

/* The x and y coordinates of the rect corresponds to its upper left corner. */

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
	img_pix_put(img, 0, i, color);
	++i;
	}
}


int	handle_keypress(int key, t_data *data)
{
	static int j;

	j = 30;
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	render(t_game *game, int x, int y, void *img)
{
	if (game->win_ptr == NULL)
		return (1);
	// render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	// render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 50, 50);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 100, 100);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x, y);
	// render_background(&data->texture.charac, WHITE_PIXEL);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture.charac.mlx_img, i, 0);

	return (0);
}


int	main(void)
{
	// t_data	data;
	t_game	game;
	
	map_test(&game);
	
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (MLX_ERROR);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map.x * 25, game.map.y * 30, "my window");
	if (game.win_ptr == NULL)
	{
		free(game.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup texture to an image*/ 
		game.texture.floor.mlx_img = mlx_xpm_file_to_image(game.mlx_ptr, "Floors.xpm", &game.texture.floor.width, &game.texture.floor.height);
		game.texture.floor2.mlx_img = mlx_xpm_file_to_image(game.mlx_ptr, "Floors2.xpm", &game.texture.floor2.width, &game.texture.floor2.height);
		game.texture.wall.mlx_img = mlx_xpm_file_to_image(game.mlx_ptr, "wall.xpm", &game.texture.wall.width, &game.texture.wall.height);
		game.texture.wall2.mlx_img = mlx_xpm_file_to_image(game.mlx_ptr, "wall2.xpm", &game.texture.wall2.width, &game.texture.wall2.height);
		game.texture.charac.mlx_img = mlx_xpm_file_to_image(game.mlx_ptr, "charac.xpm", &game.texture.charac.width, &game.texture.charac.height);
	
	// mlx_pixel_put(data.mlx_ptr, data.win_ptr, 10, 10, WHITE_PIXEL);
		
	// game.texture.floor.addr = mlx_get_data_addr(game.texture.floor.mlx_img, &game.texture.floor.bpp,
	// 		&game.texture.floor.line_len, &game.texture.floor.endian);
	
	// game.texture.charac.addr = mlx_get_data_addr(game.texture.charac.mlx_img, &game.texture.charac.bpp,
	// 		&game.texture.charac.line_len, &game.texture.charac.endian);

		map_print(&game);

		mlx_loop_hook(game.mlx_ptr, &render, &game);
		mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game);
		mlx_loop(game.mlx_ptr);

	


	/* we will exit the loop if there's no window left, and execute this code */
		mlx_destroy_image(game.mlx_ptr, game.texture.floor.mlx_img);
		mlx_destroy_image(game.mlx_ptr, game.texture.charac.mlx_img);
		mlx_destroy_display(game.mlx_ptr);
		free(game.mlx_ptr);
}


/* gerer BUG SI CARTE PlUS GRANDE QUE ECRAN*/