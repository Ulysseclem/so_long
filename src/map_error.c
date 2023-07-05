/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:04:57 by uclement          #+#    #+#             */
/*   Updated: 2023/07/05 14:22:17 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



void	map_error(t_map *map)
{
	int	i;
	int	j;
	int error_e;
	int error_p;
	char **map_bis;
	
	// taille de la carte (carre ou trop petit)
	map->x = ft_strlen(map->map[0]);
	if (map->y == map->x || (map->x < 3 && map->y < 3) || map->x * map->y < 14)
	{
		free_map(map->map, map->y);
		error_exit("error : wrong map size\n");
	}
	// ligne pas de meme taille et bordure de la carte
	i = 0;
	error_e = 0;
	error_p = 0;
	while (i < map->y)
	{
		j = 0;
		if (ft_strlen(map->map[i]) != (size_t)map->x)
			{
				free_map(map->map, map->y);
				error_exit("error : wrong row lengh\n");
			}
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '0' && map->map[i][j] != '1' && map->map[i][j] != 'C' && \
			map->map[i][j] != 'E' && map->map[i][j] != 'P')
			{
				free_map(map->map, map->y);
				error_exit("error : unkown map tiles\n");				
			}
			// gestion des bordure
			if (map->map[0][j] != '1')
			{
				free_map(map->map, map->y);
				error_exit("error : missing border tile(s)\n");
			}
			if (map->map[map->y - 1][j] != '1')
			{
				free_map(map->map, map->y);
				error_exit("error : missing border tile(s)\n");
			}
			// si trop de de E ou P - a split dans une autre fonction
			if (map->map[i][j] == 'E')
				error_e++;
			if (map->map[i][j] == 'P')
				error_p++;

			j++;
		}
		i++;
	}
	if (error_e != 1 || error_p != 1)
	{
		free_map(map->map, map->y);
		error_exit("error : wrong nbr of exit/character\n");
	}
	// sortie accessible ?
	map_find_start(map);
	map_bis = malloc(sizeof(char *) * map->y);
	i = 0;
	while (i < map->y)
	{
		map_bis[i] = ft_strcpy(map_bis[i], map->map[i]);
		i++;
	}
	map_flood(map_bis, map->start_x, map->start_y);
	if (map_flood_check(map_bis, map->y) == 1)
		{
			free_map(map_bis, map->y);
			error_exit("error : Exit unreachable");
		}

	// print test
	i = 0;
	while (i < map->y)
	{
		printf("F%c = %s\n", i, map->map[i]);
		i++;
	}
	i = 0;
	while (i < map->y)
	{
		printf("B%c = %s\n", i, map_bis[i]);
		i++;
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