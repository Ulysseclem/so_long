/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:35:25 by uclement          #+#    #+#             */
/*   Updated: 2023/06/29 18:29:47 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void map_test(t_data data)
{
	int 	fd;
	char	*line;
	char 	**map;
	int		i;
	int		size;

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
	map_print(map, data);
	free_map(map, size);
}

void map_print(char **map, t_data data)
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
				render(&data, px_x, (px_y + 14), 9);
			}
			else if (map[i][j] == '0')
				render(&data, px_x, px_y, 0);
			if ((i < 8 && map[i][j] == '1' && map[i + 1][j] == '1'))
				render(&data, px_x, px_y, 2);	
			else if (map[i][j] == '1')
				render(&data, px_x, px_y, 1);
			else if (map[i][j] == 'c')
				render(&data, px_x, px_y + 14, 5);
			px_x = px_x + 25;
			j++;
		}
		px_y = px_y + 25;
		i++;
	}
}

/*Avec la carte en array
Si j'ai un 1, j'imprime un mur
si j'ai un 0, j'imprime un sol

si */

char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;
	int 	size;

	i = 0;
	size = ft_strlen(src);
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


void	test (char *line, int ligne, t_data data)
{
	int i;
	int px;
	static char *saved;
		
	i = 0;
	px = 0;
	
	ligne = ligne * 25;
	printf("test : %s\n", saved);
	while (line[i] != '\0')
	{
		if (saved != NULL)
		{
			if (line[i] == '1' && saved[i] == '1')
				render(&data, px, ligne, 3);
		}
		else if (line[i] == '1')
			render(&data, px, ligne, 1);
		if (line[i] == '0')
			render(&data, px, ligne, 2);
		i++;
		px = px + 25;
	}
	saved = ft_strcpy(saved, line);
}

//trouver le nombre de ligne de la carte

// !!!!!!!!!!!!!!!!!!!!!!!!!!!! FAIRE UN TABLEAU DE CHAR et sauvegarder toutes les lines