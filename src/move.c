/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 16:04:59 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 16:07:26 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int move_dowm(t_game *game)
{
	if (game->map.map[game->map.start_y + 1][game->map.start_x] == 'C')
		game->map.nbr_C--;
	if  (game->map.map[game->map.start_y + 1][game->map.start_x] == 'E' && game->map.nbr_C > 0)
		return (0);
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
	else
		return(0);
	game->map.count_move++;
	return(1);
}

int move_up(t_game *game)
{
	if (game->map.map[game->map.start_y - 1][game->map.start_x] == 'C')
			game->map.nbr_C--;
	if  (game->map.map[game->map.start_y - 1][game->map.start_x] == 'E' && game->map.nbr_C > 0)
		return (0);
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
	else 
		return (0);
	game->map.count_move++;
	return(1);
}

int move_left(t_game *game)
{
	if (game->map.map[game->map.start_y][game->map.start_x - 1] == 'C')
		game->map.nbr_C--;
	if  (game->map.map[game->map.start_y][game->map.start_x - 1] == 'E' && game->map.nbr_C > 0)
		return (0);
	if (game->map.map[game->map.start_y][game->map.start_x - 1] != '1')
	{
		if (game->map.map[game->map.start_y][game->map.start_x - 1] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y][game->map.start_x - 1] = 'L';
		game->map.start_x--;
	}
	else
		return(0);
	game->map.count_move++;
	return (1);
}

int move_right(t_game *game)
{
	if (game->map.map[game->map.start_y][game->map.start_x + 1] == 'C')
		game->map.nbr_C--;
	if  (game->map.map[game->map.start_y][game->map.start_x + 1] == 'E' && game->map.nbr_C > 0)
		return (0);
	if (game->map.map[game->map.start_y][game->map.start_x + 1] != '1')
	{
		if (game->map.map[game->map.start_y][game->map.start_x + 1] == 'E')
			end(game);
		game->map.map[game->map.start_y][game->map.start_x] = '0';
		game->map.map[game->map.start_y][game->map.start_x + 1] = 'P';
		game->map.start_x++;

	}
	else 
		return(0);
	game->map.count_move++;
	return (1);
}

int	handle_input(int key, t_game *game)
{
	int i;

	i = 0;
	(void)game;
	if (key == XK_Down)
		i = move_dowm(game);
	else if (key == XK_Up)
		i = move_up(game);
	else if (key == XK_Left)
		i = move_left(game);
	else if (key == XK_Right)
		i = move_right(game);
	if (i == 1)
		ft_printf("%d\n", game->map.count_move);
	return(0);
}