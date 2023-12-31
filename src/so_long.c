/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:21:45 by ulysse            #+#    #+#             */
/*   Updated: 2023/08/01 15:11:53 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

int	handle_exit(t_game *game)
{
	game->map.count_move--;
	end(game);
	return (0);
}

int	check_file(int ac, char *av)
{
	int	i;

	i = 0;
	if (ac != 2)
		return (1);
	while (av[i] != 0)
		i++;
	if (ft_strncmp(&av[i - 4], ".ber", 4 != 0))
		return (1);
	return (0);
}

void	init_tab(t_textures *texture)
{
	t_img	*tab;

	tab = malloc(sizeof(t_img) * 24);
	texture->tab = tab;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (check_file(ac, av[1]) != 0)
		return (0);
	check_images_exist();
	map_init(&game);
	game.map.map_name = (av[1]);
	map_read(&game);
	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		error_exit_free_map("missing env", &game.map);
	game.win_ptr = mlx_new_window(game.mlx_ptr, game.map.x * 48, \
	game.map.y * 48 + 28, "so_long");
	if (game.win_ptr == NULL)
	{
		free(game.win_ptr);
		return (MLX_ERROR);
	}
	load_asset(&game.texture, game.mlx_ptr, &game);
	mlx_key_hook (game.win_ptr, &handle_input, &game);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_hook(game.win_ptr, 17, 1L << 1, &handle_exit, &game);
	mlx_loop_hook(game.mlx_ptr, &map_print, &game);
	mlx_loop(game.mlx_ptr);
}
