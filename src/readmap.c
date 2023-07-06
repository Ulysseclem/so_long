/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:35:25 by uclement          #+#    #+#             */
/*   Updated: 2023/07/05 22:57:47 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_test(t_data data)
{
	t_map	map;
	
	(void)data.mlx_ptr;
	map_init(&map);
	map_size(&map);
	map.map = map_cpy(map.map, map.y);
	map_error(&map);
	map_print(&map, data);
	free_map(map.map, map.y);
}

/* Pour connaitre la taille y de la carte */

void	map_size(t_map *map)
{
	int		fd;
	char	*line;
	fd = open("map.ber", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL && map->y == 0)
		{	
			free(line);
			error_exit("error: empty map\n");
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
void map_print(t_map *map, t_data data)
{
	int i;
	int j;
	int	px_x;
	int	px_y;

	px_y = 0;
	i = 0;
	while (i < map->y)
	{
		px_x = 0;
		j = 0;
		while (map->map[i][j])
		{
			if (i > 0 && (map->map[i][j] == '0' && map->map[i - 1][j] == '1'))
			{
				render(&data, px_x, (px_y + 18), 9);
			}
			else if (map->map[i][j] == '0')
				render(&data, px_x, px_y, 0);
			if ((i < (map->y - 1) && map->map[i][j] == '1' && map->map[i + 1][j] == '1'))
				render(&data, px_x, px_y, 2);	
			else if (map->map[i][j] == '1')
				render(&data, px_x, px_y, 1);
			else if (map->map[i][j] == 'P')
				render(&data, px_x, px_y, 5);
			px_x = px_x + 25;
			j++;
		}
		px_y = px_y + 25;
		i++;
	}
}

char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;
	int 	size;

	i = 0;
	size = ft_strlen(src);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i] && src[i] != '\n')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void free_map(char **map, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	map_init(t_map *map)
{
	map->y = 0;
	map->x = 0;
	map->nbr_PE = 0;
}

char	**map_cpy(char **map, int size)
{
	int 	fd;
	char	*line;
	int		i;
	
	map = malloc(sizeof(char *) * size);
	if (!map)
		return (0);
	fd = open("map.ber", O_RDONLY);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
		{	
			free(line);
			break ;
		}
		map[i] = ft_strcpy(map[i], line);
		// printf("L: %s\n", map.map[i]);
		free(line);
		i++;
	}
	close(fd);
	return (map);
}
