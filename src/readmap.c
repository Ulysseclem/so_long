/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:35:25 by uclement          #+#    #+#             */
/*   Updated: 2023/07/05 14:22:43 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_test(t_data data)
{
	int 	fd;
	char	*line;
	int		i;
	t_map	map;
	
	map.y = 0;
	map.x = 0;
	(void)data.mlx_ptr;

	map_size(&map);
	map.map = malloc(sizeof(char *) * map.y);
	if (!map.map)
		return ;
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
		map.map[i] = ft_strcpy(map.map[i], line);
		printf("L: %s\n", map.map[i]);
		free(line);
		i++;
	}
	close(fd);
	map_error(&map);
	// map_print(map, data, size);
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
		free(line);
		map->y++;
	}
	close(fd);
}

void map_print(char **map, t_data data, int size)
{
	int i;
	int j;
	int	px_x;
	int	px_y;

	px_y = 0;
	i = 0;
	while (map[i])
	{
		px_x = 0;
		j = 0;
		while (map[i][j])
		{
			if (i > 0 && (map[i][j] == '0' && map[i - 1][j] == '1'))
			{
				render(&data, px_x, (px_y + 18), 9);
			}
			else if (map[i][j] == '0')
				render(&data, px_x, px_y, 0);
			if ((i < (size - 1) && map[i][j] == '1' && map[i + 1][j] == '1'))
				render(&data, px_x, px_y, 2);	
			else if (map[i][j] == '1')
				render(&data, px_x, px_y, 1);
			else if (map[i][j] == 'P')
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
