/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:04:57 by uclement          #+#    #+#             */
/*   Updated: 2023/06/30 13:34:18 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_error(char **map, int y)
{
	int	x;
	int	i;
	int	j;
	
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
}