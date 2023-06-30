/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:35:25 by uclement          #+#    #+#             */
/*   Updated: 2023/06/30 13:06:55 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_test(t_data data)
{
	int 	fd;
	char	*line;
	char 	**map;
	int		i;
	int		size;

	(void)data.mlx_ptr;


	size = map_size();
	map = malloc(sizeof(map) * size + 1);
	if (!map)
		return ;
	ft_bzero(map, size + 1);
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
		printf("L: %s\n", map[i]);
		free(line);
		i++;
	}
	close(fd);
	map_error(map, size);
	// map_print(map, data, size);
	free_map(map, size);
}

/* Pour connaitre la taille y de la carte */

int	map_size(void)
{
	int		fd;
	char	*line;
	int		size;


	size = 0;
	fd = open("map.ber", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s",line);
		if (line == NULL && size == 0)
		{	
			free(line);
			error_exit();
			break ;
		}
		if (line == NULL)
		{	
			free(line);
			break ;
		}
		free(line);
		size++;
	}
	close(fd);
	return (size);
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
			else if (map[i][j] == 'c')
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
