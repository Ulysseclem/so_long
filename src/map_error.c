/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:04:57 by uclement          #+#    #+#             */
/*   Updated: 2023/07/05 12:04:39 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"



void	map_error(char **map, int y)
{
	int	x;
	int	i;
	int	j;
	int error_e;
	int error_p;
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
	error_e = 0;
	error_p = 0;
	while (i < y)
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
			// gestion des bordure
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
			// si trop de de E ou P - a split dans une autre fonction
			if (map[i][j] == 'E')
				error_e++;
			if (map[i][j] == 'P')
				error_p++;
			if (error_e > 1 || error_p > 1)
			{
				free_map(map, y);
				error_exit();
			}
			j++;
		}
		i++;
	}
	// sortie accessible ?
	start = map_find_start(map, y);
	char **map_bis;
	map_bis = malloc(sizeof(map) * y);
	i = 0;
	while (i < y)
	{
		map_bis[i] = ft_strcpy(map_bis[i], map[i]);
		i++;
	}
	map_flood(map_bis, start.x, start.y);
	if (map_flood_check(map_bis, y) == 1)
		{
			free_map(map_bis, y);
			error_exit();
		}

	// print test
	i = 0;
	while (i < y)
	{
		printf("F%c = %s\n", i, map[i]);
		i++;
	}
	i = 0;
	while (i < y)
	{
		printf("B%c = %s\n", i, map_bis[i]);
		i++;
	}
	free_map(map_bis, y);

}

t_pos map_find_start(char **map, int size)
{
	int i;
	int	j;
	t_pos start;
	
	i = 0;
	while (i < size)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
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