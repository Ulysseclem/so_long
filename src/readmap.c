/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 10:35:25 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 14:15:42 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void map_test(t_game *game)
{	
	map_size(&game->map);
	game->map.map = map_cpy(&game->map, game->map.map);
	map_error(&game->map);
}

/* Pour connaitre la taille y de la carte */

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
	map->px_x = map->x * 48;
	map->px_y = map->y * 48 + 28;
	close(fd);
}
int map_print(t_game *game)
{
	int i;
	int j;
	int	px_x;
	int	px_y;
	int	count;

	i = 0;
	px_y = 0;
	count = 0;
	while (i < game->map.y)
	{
		px_x = 0;
		j = 0;
		while (game->map.map[i][j])
		{
			/*exit*/
			if (game->map.map[i][j] == 'E' && game->map.map[i + 1][j] == 'P' && game->map.nbr_C > 0)
				render(game, px_x, (px_y + 28), game->texture.exit_lock_charac.mlx_img);
			else if (game->map.map[i][j] == 'E' && game->map.map[i + 1][j] == 'L' && game->map.nbr_C > 0)
				render(game, px_x, (px_y + 28), game->texture.exit_lock_charac_left.mlx_img);
			else if (game->map.map[i][j] == 'E' && game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L' && game->map.nbr_C > 0)
				render(game, px_x, (px_y + 28), game->texture.exit_lock.mlx_img);

			if (game->map.map[i][j] == 'E' && game->map.map[i + 1][j] == 'P' && game->map.nbr_C == 0)
				render(game, px_x, (px_y + 28), game->texture.exit_charac.mlx_img);
			else if (game->map.map[i][j] == 'E' && game->map.map[i + 1][j] == 'L' && game->map.nbr_C == 0)
				render(game, px_x, (px_y + 28), game->texture.exit_charac_left.mlx_img);
			else if (game->map.map[i][j] == 'E' && game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L' && game->map.nbr_C == 0)
				render(game, px_x, (px_y + 28), game->texture.exit.mlx_img);
			
			/*floor*/
			if (i > 0 && (game->map.map[i][j] == '0' && (game->map.map[i + 1][j] == '1')))
				render(game, px_x, (px_y + 28), game->texture.floor_half.mlx_img);
			else if (game->map.map[i][j] == '0' && (game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L'))
				render(game, px_x, px_y + 28, game->texture.floor_dirt_1.mlx_img);
			/*Wall*/
			if ((i < (game->map.y - 1) && game->map.map[i][j] == '1' && game->map.map[i + 1][j] == '1'))
				render(game, px_x, px_y, game->texture.wall_top.mlx_img);	
			else if (i < game->map.y - 1 && game->map.map[i][j] == '1'  && (game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L'))
				render(game, px_x, px_y, game->texture.wall_all.mlx_img);
			if ( i == game->map.y - 1 && game->map.map[i][j] == '1')
				render(game, px_x, px_y, game->texture.wall_all.mlx_img);
			
			/* perso move*/
			if (game->map.map[i][j] == 'P')
			{
				if (game->map.map[i - 1][j] == '1')
					render(game, px_x, px_y - 48, game->texture.charac_top_wall.mlx_img);	
				if (game->map.map[i + 1][j] == '1')
					render(game, px_x, px_y + 28, game->texture.charac_floor_half.mlx_img);
				if (game->map.map[i + 1][j] != '1')
					render(game, px_x, px_y + 28, game->texture.charac_floor.mlx_img);
				if (game->map.map[i - 1][j] == 'C')
					render(game, px_x, px_y - 20, game->texture.diamond_floor_charac.mlx_img);	
				if (game->map.map[i - 1][j] == '0')
					render(game, px_x, px_y - 20, game->texture.charac_floor_head.mlx_img);
			}
			if (game->map.map[i][j] == 'L')
			{
				if (game->map.map[i - 1][j] == '1')
					render(game, px_x, px_y - 48, game->texture.charac_top_wall_left.mlx_img);	
				if (game->map.map[i + 1][j] == '1')
					render(game, px_x, px_y + 28, game->texture.charac_floor_half_left.mlx_img);
				if (game->map.map[i + 1][j] != '1')
					render(game, px_x, px_y + 28, game->texture.charac_floor_left.mlx_img);
				if (game->map.map[i - 1][j] == 'C')
					render(game, px_x, px_y - 20, game->texture.diamond_floor_charac_left.mlx_img);
				if (game->map.map[i - 1][j] == '0')
					render(game, px_x, px_y - 20, game->texture.charac_floor_head_left.mlx_img);
			}
			/*diamond*/
			if (game->map.map[i][j] == 'C' && game->map.map[i + 1][j] == '1')
				render(game, px_x, (px_y + 28), game->texture.diamond_floor_half.mlx_img);
			else if (game->map.map[i][j] == 'C' && game->map.map[i + 1][j] != 'P' && game->map.map[i + 1][j] != 'L')
				render(game, px_x, (px_y + 28), game->texture.diamond_floor.mlx_img);

			px_x = px_x + 48;
			j++;
		}
		px_y = px_y + 48;
		i++;
	}
	return (0);
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

void	map_init(t_game *game)
{
	game->map.y = 0;
	game->map.x = 0;
	game->map.nbr_P = 0;
	game->map.nbr_E = 0;
	game->map.nbr_C = 0;
	game->map.count_move = 0;
}

char	**map_cpy(t_map *map, char **mappy)
{
	int 	fd;
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
		// printf("L: %s\n", map.map[i]);
		free(line);
		i++;
	}
	close(fd);
	return (mappy);
}
