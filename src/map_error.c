/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:04:57 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 15:51:53 by uclement         ###   ########.fr       */
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
			map_error_tiles(map->map[i][j], map);
			j++;
		}
		i++;
	}
	if (map->nbr_P + map->nbr_E != 2)
		error_exit_free_map("error : wrong nbr of Charac/Exit\n", map);
	if (map->nbr_C == 0)
		error_exit_free_map("error : no collectibles in the map\n", map);
	map_is_possible(map);
}

void map_error_tiles(char tile, t_map *map)
{
	if (tile != '0' && tile != '1' && tile!= 'C' && tile != 'E' && tile != 'P')
		error_exit_free_map("error : issues with map tiles\n", map);
	if (tile == 'P')
			map->nbr_P++;
	if (tile == 'E')
			map->nbr_E++;
	if (tile == 'C')
			map->nbr_C++;
	if (map->nbr_E > 1 || map->nbr_P > 1)
		error_exit_free_map("error : wrong nbr of Charac/Exit\n", map);

}

void map_is_possible(t_map *map)
{
	int i;

	char **map_bis;
	map_find_start(map);
	map_bis = 0;
	map_bis = map_cpy(map, map_bis);
	map_flood(map_bis, map->start_x, map->start_y);
	i = 0;
	while (i < map->y)
	{
		printf("B%c = %s\n", i, map_bis[i]);
		i++;
	}
	if (map_flood_check(map_bis, map->y) == 1)
		{
			free_map(map_bis, map->y);
			error_exit_free_map("error : Exit unreachable", map);
		}
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
				map->start_x = j;
				map->start_y = i;
			}
			j++;
		}
		i++;
	}
}

void map_flood(char **map, int x, int y)
{	
	if (map[y][x] == 'C' || map[y][x] == '0' || map[y][x] == 'E' || map[y][x] == 'P')
	{
		map[y][x] = 'X';
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
