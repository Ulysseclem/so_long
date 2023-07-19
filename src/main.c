/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:21:45 by ulysse            #+#    #+#             */
/*   Updated: 2023/07/17 19:48:49 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>


int	render(t_game *game, int x, int y, void *img)
{
	if (game->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x, y);
	return (0);
}

t_img	init_image(void *mlx, char *path)
{
	t_img	img;

	img.mlx_img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (img.mlx_img == NULL)
		error_exit("xpm non trouve");
	return (img);
}

void load_asset(t_textures *texture, t_game *game)
{
	void	*mlx;

	mlx = game->mlx_ptr;
	texture->wall_all = init_image(mlx, WALL);
	texture->wall_top = init_image(mlx, WALL_TOP);
	texture->floor_dirt_1 = init_image(mlx, FLOOR);
	texture->floor_half = init_image(mlx, FLOOR_H);
	texture->charac_floor = init_image(mlx, CHARAC);
	texture->charac_floor_half = init_image(mlx, CHARAC_H);
	texture->charac_floor_head = init_image(mlx, CHARAC_TOP);
	texture->charac_top_wall = init_image(mlx, CHARAC_TOP_W);
	texture->charac_floor_left = init_image(mlx, CHARAC_L);
	texture->charac_floor_half_left = init_image(mlx, CHARAC_H_L);
	texture->charac_floor_head_left = init_image(mlx, CHARAC_TOP_L);
	texture->charac_top_wall_left = init_image(mlx, CHARAC_TOP_W_L);
	texture->diamond_floor = init_image(mlx, DIAMOND);
	texture->diamond_floor_half = init_image(mlx, DIAMOND_H);
	texture->diamond_floor_charac = init_image(mlx, DIAMOND_C);
	texture->diamond_floor_charac_left = init_image(mlx, DIAMOND_C_L);
	texture->exit = init_image(mlx, EXIT);
	texture->exit_charac = init_image(mlx, EXIT_C);
	texture->exit_charac_left = init_image(mlx, EXIT_C_L);
	texture->exit_lock = init_image(mlx, EXIT_LCK);
	texture->exit_lock_charac = init_image(mlx, EXIT_LCK_C);
	texture->exit_lock_charac_left = init_image(mlx, EXIT_LCK_C_L);
}


int check_file(int ac, char *av)
{
	int i;

	i = 0;
	if (ac != 2)
		return (1);
	while (av[i] != 0)
		i++;
	if (ft_strncmp(&av[i - 4], ".ber", 4 != 0))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (check_file(ac, av[1]) != 0)
		return (0);
	map_init(&game);
	game.map.map_name = (av[1]);
	map_test(&game);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (MLX_ERROR);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map.px_x, \
	game.map.px_y, "so_long");
	if (game.win_ptr == NULL)
	{
		free(game.win_ptr);
		return (MLX_ERROR);
	}
	load_asset(&game.texture, &game);
	mlx_key_hook (game.win_ptr, &handle_input, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_loop_hook(game.mlx_ptr, &map_print, &game);
	mlx_loop(game.mlx_ptr);
}