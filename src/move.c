/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:04:59 by uclement          #+#    #+#             */
/*   Updated: 2023/08/01 13:09:59 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_dowm(t_map *map, t_game *game)
{
	if (map->map[map->start_y + 1][map->start_x] == '1')
		return ;
	if (map->map[map->start_y + 1][map->start_x] == 'E' && map->nbr_c > 0)
	{
		if (map->map[map->start_y + 2][map->start_x] == '1')
			return ;
		if (map->map[map->start_y][map->start_x] == 'L')
			map->map[map->start_y + 2][map->start_x] = 'L';
		else if (map->map[map->start_y][map->start_x] == 'P')
			map->map[map->start_y + 2][map->start_x] = 'P';
		map->map[map->start_y][map->start_x] = '0';
		map->start_y = map->start_y + 2;
		return ;
	}
	if (map->map[map->start_y + 1][map->start_x] == 'E')
		end(game);
	if (map->map[map->start_y + 1][map->start_x] != '1' && \
	map->map[map->start_y][map->start_x] == 'L')
	map->map[map->start_y + 1][map->start_x] = 'L';
	else if (map->map[map->start_y + 1][map->start_x] != '1')
		map->map[map->start_y + 1][map->start_x] = 'P';
	map->map[map->start_y][map->start_x] = '0';
	map->start_y++;
}

void	move_up(t_map *map, t_game *game)
{
	if (map->map[map->start_y - 1][map->start_x] == '1')
		return ;
	if (map->map[map->start_y - 1][map->start_x] == 'E' && map->nbr_c > 0)
	{
		if (map->map[map->start_y - 2][map->start_x] == '1')
			return ;
		if (map->map[map->start_y][map->start_x] == 'L')
			map->map[map->start_y - 2][map->start_x] = 'L';
		else if (map->map[map->start_y][map->start_x] == 'P')
			map->map[map->start_y - 2][map->start_x] = 'P';
		map->map[map->start_y][map->start_x] = '0';
		map->start_y = map->start_y - 2;
		return ;
	}
	if (map->map[map->start_y - 1][map->start_x] == 'E' && map->nbr_c == 0)
		end(game);
	if (map->map[map->start_y - 1][map->start_x] != '1' && \
	map->map[map->start_y][map->start_x] == 'L')
		map->map[map->start_y - 1][map->start_x] = 'L';
	else if (map->map[map->start_y - 1][map->start_x] != '1')
		map->map[map->start_y - 1][map->start_x] = 'P';
	map->map[map->start_y][map->start_x] = '0';
	map->start_y--;
}

void	move_left(t_map *map, t_game *game)
{
	if (map->map[map->start_y][map->start_x - 1] == 'E' && map->nbr_c > 0)
	{
		if (map->map[map->start_y][map->start_x - 2] == '1')
			return ;
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y][map->start_x - 2] = 'L';
		map->start_x = map->start_x - 2;
		return ;
	}
	if (map->map[map->start_y][map->start_x - 1] != '1')
	{
		if (map->map[map->start_y][map->start_x - 1] == 'E')
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y][map->start_x - 1] = 'L';
		map->start_x--;
	}
}

void	move_right(t_map *map, t_game *game)
{
	if (map->map[map->start_y][map->start_x + 1] == 'E' && map->nbr_c > 0)
	{
		if (map->map[map->start_y][map->start_x + 2] == '1')
			return ;
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y][map->start_x + 2] = 'P';
		map->start_x = map->start_x + 2;
		return ;
	}
	if (map->map[map->start_y][map->start_x + 1] != '1')
	{
		if (map->map[map->start_y][map->start_x + 1] == 'E' && map->nbr_c == 0)
			end(game);
		map->map[map->start_y][map->start_x] = '0';
		map->map[map->start_y][map->start_x + 1] = 'P';
		map->start_x++;
	}
}

int	handle_input(int key, t_game *game)
{
	int	test;
	int	test2;

	test = game->map.start_x;
	test2 = game->map.start_y;
	if (key == XK_Down)
		move_dowm(&game->map, game);
	else if (key == XK_Up)
		move_up(&game->map, game);
	else if (key == XK_Left)
		move_left(&game->map, game);
	else if (key == XK_Right)
		move_right(&game->map, game);
	if (test != game->map.start_x || test2 != game->map.start_y)
		ft_printf("%d\n", ++game->map.count_move);
	map_find_diamond(&game->map);
	return (0);
}
