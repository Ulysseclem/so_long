/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:04:59 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 11:19:33 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_dowm(t_map *map, t_game *game)
{
	if (map->map[map->start_y + 1][map->start_x] == 'C')
		map->nbr_c--;
	if (map->map[map->start_y + 1][map->start_x] == 'E' && map->nbr_c > 0)
		return (0);
	if (map->map[map->start_y + 1][map->start_x] != '1' && \
	map->map[map->start_y][map->start_x] == 'L')
	{
		if (map->map[map->start_y + 1][map->start_x] == 'E')
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y + 1][map->start_x] = 'L';
		map->start_y++;
	}
	else if (map->map[map->start_y + 1][map->start_x] != '1')
	{
		if (map->map[map->start_y + 1][map->start_x] == 'E')
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y + 1][map->start_x] = 'P';
		map->start_y++;
	}
	else
		return (0);
	map->count_move++;
	return (1);
}

int	move_up(t_map *map, t_game *game)
{
	if (map->map[map->start_y - 1][map->start_x] == 'C')
			map->nbr_c--;
	if (map->map[map->start_y - 1][map->start_x] == 'E' && map->nbr_c > 0)
		return (0);
	if (map->map[map->start_y - 1][map->start_x] != '1' && \
	map->map[map->start_y][map->start_x] == 'L')
	{
		if (map->map[map->start_y - 1][map->start_x] == 'E')
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y - 1][map->start_x] = 'L';
		map->start_y--;
	}
	else if (map->map[map->start_y - 1][map->start_x] != '1')
	{
		if (map->map[map->start_y - 1][map->start_x] == 'E')
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y - 1][map->start_x] = 'P';
		map->start_y--;
	}
	else
		return (0);
	map->count_move++;
	return (1);
}

int	move_left(t_map *map, t_game *game)
{
	if (map->map[map->start_y][map->start_x - 1] == 'C')
		map->nbr_c--;
	if (map->map[map->start_y][map->start_x - 1] == 'E' && map->nbr_c > 0)
		return (0);
	if (map->map[map->start_y][map->start_x - 1] != '1')
	{
		if (map->map[map->start_y][map->start_x - 1] == 'E')
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y][map->start_x - 1] = 'L';
		map->start_x--;
	}
	else
		return (0);
	map->count_move++;
	return (1);
}

int	move_right(t_map *map, t_game *game)
{
	if (map->map[map->start_y][map->start_x + 1] == 'C')
		map->nbr_c--;
	if (map->map[map->start_y][map->start_x + 1] == 'E' && map->nbr_c > 0)
		return (0);
	if (map->map[map->start_y][map->start_x + 1] != '1')
	{
		if (map->map[map->start_y][map->start_x + 1] == 'E')
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y][map->start_x + 1] = 'P';
		map->start_x++;
	}
	else
		return (0);
	map->count_move++;
	return (1);
}

int	handle_input(int key, t_game *game)
{
	int	i;

	i = 0;
	(void)game;
	if (key == XK_Down)
		i = move_dowm(&game->map, game);
	else if (key == XK_Up)
		i = move_up(&game->map, game);
	else if (key == XK_Left)
		i = move_left(&game->map, game);
	else if (key == XK_Right)
		i = move_right(&game->map, game);
	if (i == 1)
		ft_printf("%d\n", game->map.count_move);
	return (0);
}
