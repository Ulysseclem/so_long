/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:04:57 by uclement          #+#    #+#             */
/*   Updated: 2023/07/04 18:56:34 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error(char **map, int y)
{
	int	x;
	int	i;
	int	j;
	t_pos start;
	
	// taille de la carte (carre ou trop petit)
	x = ft_strlen(map[0]);
	if (y == x || (x < 3 && y < 3) || x * y < 14)
	{
		free_map(map, y);
		error_exit();
	}
	// ligne pas de meme taille et bordure de la carte
	i = 0;
	while (map[i])
	{
		j = 0;
		if (ft_strlen(map[i]) != (size_t)x)
			{
				free_map(map, y);
				error_exit();
			}
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != 'C' && \
			map[i][j] != 'E' && map[i][j] != 'P')
			{
				free_map(map, y);
				error_exit();				
			}
			if (map[0][j] != '1')
			{
				free_map(map, y);
				error_exit();
			}
			if (map[y - 1][j] != '1')
			{
				free_map(map, y);
				error_exit();
			}
			j++;
		}
		i++;
	}
	start = map_find_start(map);
	map_flood(map, start.x, start.y);
	if (map_flood_check(map) == 1)
		{
			free_map(map, y);
			error_exit();
		}	
	//priint test
	i = 0;		
	while (map[i])
	{
		printf("F%c = %s\n", i, map[i]);
		i++;
	}
}

t_pos map_find_start(char **map)
{
	int i;
	int	j;
	t_pos start;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
			{
				start.x = i;
				start.y = j;
			}
			j++;
		}
		i++;
	}
	return (start);
}

void map_flood(char **map, int x, int y)
{	
	if (map[x][y] == 'C' || map[x][y] == '0' || map[x][y] == 'E')
	{
		map[x][y] = 'X';
		map_flood(map, x + 1, y);
		map_flood(map, x - 1, y);
		map_flood(map, x, y + 1);
		map_flood(map, x, y - 1);
	}
}

int	map_flood_check(char **map)
{
	int i;
	int j;
	i =0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}