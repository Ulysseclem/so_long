/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:04:57 by uclement          #+#    #+#             */
/*   Updated: 2023/07/05 22:38:59 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error(t_map *map)
{
	int	i;
	int	j;
	
	if (map->y == map->x || (map->x < 3 && map->y < 3) || map->x * map->y < 14)
		error_exit_free_map("error : wrong map size\n", map);
	i = 0;
	while (i < map->y)
	{
		j = 0;
		if (ft_strlen(map->map[i]) != (size_t)map->x)
				error_exit_free_map("error : wrong row lengh\n", map);
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '0' && map->map[i][j] != '1' && \
			map->nbr_PE != 2 && map->map[i][j] != 'C' && \
			map->map[i][j] != 'E' && map->map[i][j] != 'P' && \
			(map->map[0][j] != '1' || map->map[map->y - 1][j] != '1'))
				error_exit_free_map("error : issues wuth map tiles\n", map);	
			if (map->map[i][j] == 'E' || map->map[i][j] == 'P')
				map->nbr_PE++;
			j++;
		}
		i++;
	}
	map_is_possible(map);
}

void map_is_possible(t_map *map)
{
	char **map_bis;
	map_find_start(map);
	map_bis = 0;
	map_bis = map_cpy(map_bis, map->y);
	map_flood(map_bis, map->start_x, map->start_y);
	if (map_flood_check(map_bis, map->y) == 1)
		{
			free_map(map_bis, map->y);
			error_exit_free_map("error : Exit unreachable", map);
		}
	// // print test
	// i = 0;
	// while (i < map->y)
	// {
	// 	printf("F%c = %s\n", i, map->map[i]);
	// 	i++;
	// }
	// i = 0;
	// while (i < map->y)
	// {
	// 	printf("B%c = %s\n", i, map_bis[i]);
	// 	i++;
	// }
	free_map(map_bis, map->y);
}

void map_find_start(t_map *map)
{
	int i;
	int	j;
	
	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
			{
				map->start_x = i;
				map->start_y = j;
			}
			j++;
		}
		i++;
	}
}

void map_flood(char **map, int x, int y)
{	
	if (map[x][y] == 'C' || map[x][y] == '0' || map[x][y] == 'E' || map[x][y] == 'P')
	{
		map[x][y] = 'X';
		map_flood(map, x + 1, y);
		map_flood(map, x - 1, y);
		map_flood(map, x, y + 1);
		map_flood(map, x, y - 1);
	}
}

int	map_flood_check(char **map, int size)
{
	int i;
	int j;

	i =0;
	while (i < size)
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
