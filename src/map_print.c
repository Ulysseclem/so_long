/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:02:10 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 12:53:02 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	map_print(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	game->map.px_y = 0;
	while (i < game->map.y)
	{
		game->map.px_x = 0;
		j = 0;
		while (game->map.map[i][j])
		{
			if (game->map.map[i][j] == 'E')
				print_exit(game, &game->map, i, j);
			print_floor_wall_diamond(game, &game->map, i, j);
			print_charac(game, &game->map, i, j);
			print_charac_left(game, &game->map, i, j);
			game->map.px_x = game->map.px_x + 48;
			j++;
		}
		game->map.px_y = game->map.px_y + 48;
		i++;
	}
	return (0);
}

void	print_exit(t_game *game, t_map *map, int i, int j)
{
	if (map->map[i + 1][j] == 'P' && map->nbr_c > 0)
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.exit_lock_charac.mlx_img);
	else if (map->map[i + 1][j] == 'L' && map->nbr_c > 0)
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.exit_lock_charac_left.mlx_img);
	else if (map->nbr_c > 0 && map->map[i + 1][j] == '1')
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.exit_lock_half.mlx_img);
	else if (map->map[i + 1][j] != 'P' && \
	map->map[i + 1][j] != 'L' && map->nbr_c > 0 && map->map[i + 1][j] != '1')
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.exit_lock.mlx_img);
	else if (map->map[i + 1][j] == 'P' && map->nbr_c == 0)
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.exit_charac.mlx_img);
	else if (map->map[i + 1][j] == 'L' && map->nbr_c == 0)
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.exit_charac_left.mlx_img);
	else if (map->map[i + 1][j] == '1')
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.exit_half.mlx_img);
	else if (map->map[i + 1][j] != 'P' && \
	map->map[i + 1][j] != 'L' && map->nbr_c == 0 && map->map[i + 1][j] != '1')
		render(game, map->px_x, (map->px_y + 28), game->texture.exit.mlx_img);
}

void	print_floor_wall_diamond(t_game *game, t_map *map, int i, int j)
{
	if (i > 0 && (game->map.map[i][j] == '0' && \
	(game->map.map[i + 1][j] == '1')))
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.floor_half.mlx_img);
	else if (game->map.map[i][j] == '0' && \
	(game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L'))
		render(game, map->px_x, map->px_y + 28, \
		game->texture.floor_dirt_1.mlx_img);
	if ((i < (game->map.y - 1) && \
	game->map.map[i][j] == '1' && game->map.map[i + 1][j] == '1'))
		render(game, map->px_x, map->px_y, game->texture.wall_top.mlx_img);
	else if (i < game->map.y - 1 && game->map.map[i][j] == '1' && \
	(game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L'))
		render(game, map->px_x, map->px_y, game->texture.wall_all.mlx_img);
	if (i == game->map.y - 1 && game->map.map[i][j] == '1')
		render(game, map->px_x, map->px_y, game->texture.wall_all.mlx_img);
	if (game->map.map[i][j] == 'C' && game->map.map[i + 1][j] == '1')
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.diamond_floor_half.mlx_img);
	else if (game->map.map[i][j] == 'C' && \
	game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L')
		render(game, map->px_x, (map->px_y + 28), \
		game->texture.diamond_floor.mlx_img);
}

void	print_charac(t_game *game, t_map *map, int i, int j)
{
	if (game->map.map[i][j] == 'P')
	{
		if (game->map.map[i - 1][j] == '1')
			render(game, map->px_x, map->px_y - 48, \
			game->texture.charac_top_wall.mlx_img);
		if (game->map.map[i + 1][j] == '1')
			render(game, map->px_x, map->px_y + 28, \
			game->texture.charac_floor_half.mlx_img);
		if (game->map.map[i + 1][j] != '1')
			render(game, map->px_x, map->px_y + 28, \
			game->texture.charac_floor.mlx_img);
		if (game->map.map[i - 1][j] == 'C')
			render(game, map->px_x, map->px_y - 20, \
			game->texture.diamond_floor_charac.mlx_img);
		if (game->map.map[i - 1][j] == '0')
			render(game, map->px_x, map->px_y - 20, \
			game->texture.charac_floor_head.mlx_img);
	}
}

void	print_charac_left(t_game *game, t_map *map, int i, int j)
{
	if (game->map.map[i][j] == 'L')
	{
		if (game->map.map[i - 1][j] == '1')
			render(game, map->px_x, map->px_y - 48, \
			game->texture.charac_top_wall_left.mlx_img);
		if (game->map.map[i + 1][j] == '1')
			render(game, map->px_x, map->px_y + 28, \
			game->texture.charac_floor_half_left.mlx_img);
		if (game->map.map[i + 1][j] != '1')
			render(game, map->px_x, map->px_y + 28, \
			game->texture.charac_floor_left.mlx_img);
		if (game->map.map[i - 1][j] == 'C')
			render(game, map->px_x, map->px_y - 20, \
			game->texture.diamond_floor_charac_left.mlx_img);
		if (game->map.map[i - 1][j] == '0')
			render(game, map->px_x, map->px_y - 20, \
			game->texture.charac_floor_head_left.mlx_img);
	}
}
