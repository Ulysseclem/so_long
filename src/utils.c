/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:04:44 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 11:23:13 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;
	int		size;

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

void	free_map(char **map, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	map_init(t_game *game)
{
	game->map.y = 0;
	game->map.x = 0;
	game->map.nbr_p = 0;
	game->map.nbr_e = 0;
	game->map.nbr_c = 0;
	game->map.count_move = 0;
}
