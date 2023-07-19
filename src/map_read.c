/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:35:25 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 17:25:57 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	map_read(t_game *game)
{	
	map_size(&game->map);
	game->map.map = map_cpy(&game->map, game->map.map);
	map_error(&game->map);
}

void	map_size(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->map_name, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL && map->y == 0)
		{	
			free(line);
			error_exit("error: no map / empty map\n");
			break ;
		}
		if (line == NULL)
		{	
			free(line);
			break ;
		}
		map->x = ft_strlen(line);
		free(line);
		map->y++;
	}
	close(fd);
}

char	**map_cpy(t_map *map, char **mappy)
{
	int		fd;
	char	*line;
	int		i;

	mappy = malloc(sizeof(char *) * map->y);
	if (!mappy)
		return (0);
	fd = open(map->map_name, O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{	
			free(line);
			break ;
		}
		mappy[i] = ft_strcpy(mappy[i], line);
		free(line);
		i++;
	}
	close(fd);
	return (mappy);
}

void	map_find_start(t_map *map)
{
	int	i;
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

void	map_find_diamond(t_map *map)
{
	int	i;
	int	j;
	int	d;

	d = 0;
	i = 0;
	while (i < map->y)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'C')
				d++;
			j++;
		}
		i++;
	}
	map->nbr_c = d;
}
