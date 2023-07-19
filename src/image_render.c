/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:37:58 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 15:23:38 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	render(t_game *game, int x, int y, void *img)
{
	if (game->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x, y);
	return (0);
}

t_img	init_image(void *mlx, char *path, t_game *game)
{
	t_img	img;

	img.mlx_img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (img.mlx_img == NULL)
	{
		end(game);
		error_exit("xpm non trouve");
	}
	return (img);
}

void	load_asset(t_textures *texture, void *mlx, t_game *game)
{
	texture->wall_all = init_image(mlx, WALL, game);
	texture->wall_top = init_image(mlx, WALL_TOP, game);
	texture->floor_dirt_1 = init_image(mlx, FLOOR, game);
	texture->floor_half = init_image(mlx, FLOOR_H, game);
	texture->charac_floor = init_image(mlx, CHARAC, game);
	texture->charac_floor_half = init_image(mlx, CHARAC_H, game);
	texture->charac_floor_head = init_image(mlx, CHARAC_TOP, game);
	texture->charac_top_wall = init_image(mlx, CHARAC_TOP_W, game);
	texture->charac_floor_left = init_image(mlx, CHARAC_L, game);
	texture->charac_floor_half_left = init_image(mlx, CHARAC_H_L, game);
	texture->charac_floor_head_left = init_image(mlx, CHARAC_TOP_L, game);
	texture->charac_top_wall_left = init_image(mlx, CHARAC_TOP_W_L, game);
	texture->diamond_floor = init_image(mlx, DIAMOND, game);
	texture->diamond_floor_half = init_image(mlx, DIAMOND_H, game);
	texture->diamond_floor_charac = init_image(mlx, DIAMOND_C, game);
	texture->diamond_floor_charac_left = init_image(mlx, DIAMOND_C_L, game);
	texture->exit = init_image(mlx, EXIT, game);
	texture->exit_half = init_image(mlx, EXIT_H, game);
	texture->exit_charac = init_image(mlx, EXIT_C, game);
	texture->exit_charac_left = init_image(mlx, EXIT_C_L, game);
	texture->exit_lock = init_image(mlx, EXIT_LCK, game);
	texture->exit_lock_half = init_image(mlx, EXIT_LCK_H, game);
	texture->exit_lock_charac = init_image(mlx, EXIT_LCK_C, game);
	texture->exit_lock_charac_left = init_image(mlx, EXIT_LCK_C_L, game);
}
