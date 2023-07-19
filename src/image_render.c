/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_render.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:37:58 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 11:48:15 by uclement         ###   ########.fr       */
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

t_img	init_image(void *mlx, char *path)
{
	t_img	img;

	img.mlx_img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (img.mlx_img == NULL)
		error_exit("xpm non trouve");
	return (img);
}

void	load_asset(t_textures *texture, t_game *game)
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
