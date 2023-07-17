/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:21:45 by ulysse            #+#    #+#             */
/*   Updated: 2023/07/11 13:24:15 by ulysse           ###   ########.fr       */
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

int	handle_keypress(int key, t_game *game)
{
	static int j;

	j = 30;
	if (key == XK_Escape)
	{
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	}
	return (0);
}

int	render(t_game *game, int x, int y, void *img)
{
	if (game->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x, y);

	return (0);
}

void move_dowm(t_game *game)
{
	if (game->map.map[game->map.start_y + 1][game->map.start_x] == 'C')
		game->map.nbr_C--;
	if  (game->map.map[game->map.start_y + 1][game->map.start_x] == 'E' && game->map.nbr_C > 0)
		return;
	if (game->map.map[game->map.start_y + 1][game->map.start_x] != '1' && game->map.map[game->map.start_y][game->map.start_x] == 'L')
	{
		if (game->map.map[game->map.start_y + 1][game->map.start_x] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y + 1][game->map.start_x] = 'L';
		game->map.start_y++;
	}
	else if (game->map.map[game->map.start_y + 1][game->map.start_x] != '1')
	{
		if (game->map.map[game->map.start_y + 1][game->map.start_x] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y + 1][game->map.start_x] = 'P';
		game->map.start_y++;
	}
	return;
}

void move_up(t_game *game)
{
	if (game->map.map[game->map.start_y - 1][game->map.start_x] == 'C')
			game->map.nbr_C--;
	if  (game->map.map[game->map.start_y - 1][game->map.start_x] == 'E' && game->map.nbr_C > 0)
		return;
	if (game->map.map[game->map.start_y - 1][game->map.start_x] != '1' && game->map.map[game->map.start_y][game->map.start_x] == 'L')
	{
		if (game->map.map[game->map.start_y - 1][game->map.start_x] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y - 1][game->map.start_x] = 'L';
		game->map.start_y--;
	}
	else if (game->map.map[game->map.start_y - 1][game->map.start_x] != '1')
	{
		if (game->map.map[game->map.start_y - 1][game->map.start_x] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y - 1][game->map.start_x] = 'P';
		game->map.start_y--;
	}
	return;
}

void move_left(t_game *game)
{
	if (game->map.map[game->map.start_y][game->map.start_x - 1] == 'C')
		game->map.nbr_C--;
	if  (game->map.map[game->map.start_y][game->map.start_x - 1] == 'E' && game->map.nbr_C > 0)
		return;
	if (game->map.map[game->map.start_y][game->map.start_x - 1] != '1')
	{
		if (game->map.map[game->map.start_y][game->map.start_x - 1] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y][game->map.start_x - 1] = 'L';
		game->map.start_x--;
	}
	return;
}

void move_right(t_game *game)
{
	if (game->map.map[game->map.start_y][game->map.start_x + 1] == 'C')
		game->map.nbr_C--;
	if  (game->map.map[game->map.start_y][game->map.start_x + 1] == 'E' && game->map.nbr_C > 0)
		return;
	if (game->map.map[game->map.start_y][game->map.start_x + 1] != '1')
	{
		if (game->map.map[game->map.start_y][game->map.start_x + 1] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y][game->map.start_x + 1] = 'P';
		game->map.start_x++;
	}
	return;
}

int	handle_input(int key, t_game *game)
{
	(void)game;
	if (key == XK_Down)
		move_dowm(game);
	else if (key == XK_Up)
		move_up(game);
	else if (key == XK_Left)
		move_left(game);
	else if (key == XK_Right)
		move_right(game);
	return(0);
}

void load_asset(t_textures *texture, t_game *game)
{
	texture->floor_dirt_1.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/floor_dirt_1.xpm", &texture->width, &texture->height);
	texture->floor_half.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/floor_half.xpm", &texture->width, &texture->height);

	texture->wall_all.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/wall_all.xpm", &texture->width, &texture->height);
	texture->wall_top.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/wall_top.xpm", &texture->width, &texture->height);

	texture->charac_floor.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_floor.xpm", &texture->width, &texture->height);
	texture->charac_floor_half.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_floor_half.xpm", &texture->width, &texture->height);
	texture->charac_floor_head.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_floor_head.xpm", &texture->width, &texture->height);
	texture->charac_top_wall.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_top_wall.xpm", &texture->width, &texture->height);

	texture->charac_floor_left.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_floor_left.xpm", &texture->width, &texture->height);
	texture->charac_floor_half_left.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_floor_half_left.xpm", &texture->width, &texture->height);
	texture->charac_floor_head_left.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_floor_head_left.xpm", &texture->width, &texture->height);
	texture->charac_top_wall_left.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/charac_top_wall_left.xpm", &texture->width, &texture->height);

	texture->diamond_floor.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/diamond_floor.xpm", &texture->width, &texture->height);
	texture->diamond_floor_half.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/diamond_floor_half.xpm", &texture->width, &texture->height);
	texture->diamond_floor_charac.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/diamond_floor_charac.xpm", &texture->width, &texture->height);
	texture->diamond_floor_charac_left.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/diamond_floor_charac_left.xpm", &texture->width, &texture->height);
	
	texture->exit.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/exit.xpm", &texture->width, &texture->height);
	texture->exit_charac.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/exit_charac.xpm", &texture->width, &texture->height);
	texture->exit_charac_left.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/exit_charac_left.xpm", &texture->width, &texture->height);

	texture->exit_lock.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/exit_lock.xpm", &texture->width, &texture->height);
	texture->exit_lock_charac.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/exit_lock_charac.xpm", &texture->width, &texture->height);
	texture->exit_lock_charac_left.mlx_img = mlx_xpm_file_to_image(game->mlx_ptr, \
	"xpm/exit_lock_charac_left.xpm", &texture->width, &texture->height);
}


void end(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->texture.floor_dirt_1.mlx_img);
	mlx_destroy_image(game->mlx_ptr, game->texture.floor_half.mlx_img);
	mlx_destroy_image(game->mlx_ptr, game->texture.wall_all.mlx_img);
	mlx_destroy_image(game->mlx_ptr, game->texture.wall_top.mlx_img);
	mlx_destroy_image(game->mlx_ptr, game->texture.charac_floor.mlx_img);
	mlx_destroy_image(game->mlx_ptr, game->texture.charac_floor_head.mlx_img);
	mlx_destroy_image(game->mlx_ptr, game->texture.diamond_floor.mlx_img);
	mlx_destroy_image(game->mlx_ptr, game->texture.exit.mlx_img);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	// mlx_destroy_display(game->mlx_ptr);
	game->win_ptr = NULL;
}

int	main(void)
{
	// t_data	data;
	t_game	game;
	
	map_test(&game);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (MLX_ERROR);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map.x * 50, game.map.y * 50, "my window");
	if (game.win_ptr == NULL)
	{
		free(game.win_ptr);
		return (MLX_ERROR);
	}
	/* Setup texture to an image*/
	load_asset(&game.texture, &game);
	
	mlx_key_hook (game.win_ptr, &handle_input, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_loop_hook(game.mlx_ptr, &map_print, &game);
	mlx_loop(game.mlx_ptr);

	free(game.mlx_ptr);
}


/* gerer BUG SI CARTE PlUS GRANDE QUE ECRAN*/