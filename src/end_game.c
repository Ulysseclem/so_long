/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:21:45 by ulysse            #+#    #+#             */
/*   Updated: 2023/07/24 15:35:23 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (key == XK_Escape)
	{
		game->map.count_move--;
		end(game);
	}

	return (0);
}

void	free_assets(void *ptr, t_textures *texture)
{
	mlx_destroy_image(ptr, texture->wall_all.mlx_img);
	mlx_destroy_image(ptr, texture->wall_top.mlx_img);
	mlx_destroy_image(ptr, texture->floor_dirt_1.mlx_img);
	mlx_destroy_image(ptr, texture->floor_half.mlx_img);
	mlx_destroy_image(ptr, texture->charac_floor.mlx_img);
	mlx_destroy_image(ptr, texture->charac_floor_half.mlx_img);
	mlx_destroy_image(ptr, texture->charac_floor_head.mlx_img);
	mlx_destroy_image(ptr, texture->charac_top_wall.mlx_img);
	mlx_destroy_image(ptr, texture->charac_floor_left.mlx_img);
	mlx_destroy_image(ptr, texture->charac_floor_half_left.mlx_img);
	mlx_destroy_image(ptr, texture->charac_floor_head_left.mlx_img);
	mlx_destroy_image(ptr, texture->charac_top_wall_left.mlx_img);
	mlx_destroy_image(ptr, texture->diamond_floor.mlx_img);
	mlx_destroy_image(ptr, texture->diamond_floor_half.mlx_img);
	mlx_destroy_image(ptr, texture->diamond_floor_charac.mlx_img);
	mlx_destroy_image(ptr, texture->diamond_floor_charac_left.mlx_img);
	mlx_destroy_image(ptr, texture->exit.mlx_img);
	mlx_destroy_image(ptr, texture->exit_half.mlx_img);
	mlx_destroy_image(ptr, texture->exit_charac.mlx_img);
	mlx_destroy_image(ptr, texture->exit_charac_left.mlx_img);
	mlx_destroy_image(ptr, texture->exit_lock.mlx_img);
	mlx_destroy_image(ptr, texture->exit_lock_half.mlx_img);
	mlx_destroy_image(ptr, texture->exit_lock_charac.mlx_img);
	mlx_destroy_image(ptr, texture->exit_lock_charac_left.mlx_img);
}

void	end(t_game *game)
{
	ft_printf("total move :%d\nEND\n", game->map.count_move + 1);
	free_assets(game->mlx_ptr, &game->texture);
	free_map(game->map.map, game->map.y);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		game->win_ptr = NULL;
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit (0);
}
