/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 11:04:44 by uclement          #+#    #+#             */
/*   Updated: 2023/07/19 15:18:17 by uclement         ###   ########.fr       */
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
	game->texture.count = 0;
}

char	*get_xpm_filename(int i)
{
	static char	*xpm_filename[] = {
		WALL, WALL_TOP, FLOOR, FLOOR_H, CHARAC, CHARAC_L,
		CHARAC_H, CHARAC_H_L, CHARAC_TOP, CHARAC_TOP_L,
		CHARAC_TOP_W, CHARAC_TOP_W_L, DIAMOND, DIAMOND_H,
		DIAMOND_C, DIAMOND_C_L, EXIT, EXIT_H, EXIT_C,
		EXIT_C_L, EXIT_LCK, EXIT_LCK_H, EXIT_LCK_C,
		EXIT_LCK_C_L,
	};

	return (xpm_filename[i]);
}

void	check_images_exist(void)
{
	int		i;
	int		fd;
	char	*filename;

	i = 0;
	while (i < XPM_IMG_COUNT)
	{
		filename = get_xpm_filename(i);
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			error_exit("missing xpm file");
		}
		close(fd);
		i++;
	}
}
