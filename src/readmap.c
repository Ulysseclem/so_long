/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:35:25 by uclement          #+#    #+#             */
/*   Updated: 2023/06/28 13:27:38 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_test(t_data data)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
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
		test(line, i, data);
		free(line);
		i++;
	}
	close(fd);
}

char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;
	int 	size;

	i = 0;
	size = ft_strlen(src);
	dest = malloc(sizeof(char) * size + 1);
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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!! FAIRE UN TABLEAU DE CHAR et sauvegarder toutes les lines