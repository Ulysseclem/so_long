/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:21:45 by ulysse            #+#    #+#             */
/*   Updated: 2023/07/18 09:36:42 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>


int	handle_keypress(int key)
{
	static int j;

	j = 30;
	if (key == XK_Escape)
		exit(0);
	return (0);
}

// void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

int	render(t_game *game, int x, int y, void *img)
{
	if (game->win_ptr == NULL)
		return (1);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, img, x, y);
	return (0);
}

t_pixel	*img_get_pixel(t_img *img, int x, int y)
{
	return (img->addr + y * img->width + x);
}

void load_asset(t_textures *texture, t_game *game)
{
	void	*mlx;
	t_pixel test;


	mlx = game->mlx_ptr;
	texture->floor_dirt_1 = init_image(mlx, FLOOR);
	texture->charac_floor = init_image(mlx, "test.xpm");
	texture->charac_floor_half = init_image(mlx, "test2.xpm");
	// (*img_get_pixel(&texture->floor_dirt_1, 47, 47)) = 	(*img_get_pixel(&texture->charac_floor, 100, 47));


	test = (*img_get_pixel(&texture->charac_floor_half, 1, 1));
	printf ("%x %x %x\n", test.r, test.g, test.b);
	
	int	j;
	int i = 0;
	while (i < 48)
	{
		j = 0;
		while (j < 48)
		{

			(*img_get_pixel(&texture->charac_floor, i, j)) = (*img_get_pixel(&texture->floor_dirt_1, i, j));
			j++;
		}
		i++;
	}
	i = 0;
	while (i < 48)
	{
		j = 0;
		while (j < 48)
		{

			(*img_get_pixel(&texture->charac_floor, i, j)) = (*img_get_pixel(&texture->charac_floor_half, i, j));
			j++;
		}
		i++;
	}
}

void	render_background(t_game *game, int color)
{
    int	i;
    int	j;

    if (game->win_ptr == NULL)
        return ;
    i = 0;
    while (i < 100)
    {
        j = 0;
        while (j < 1000)
            mlx_pixel_put(game->mlx_ptr,game->win_ptr, j++, i, color);
        ++i;
    }
}

t_img	init_image(void *mlx, char *path)
{
	t_img	img;

	img.mlx_img = mlx_xpm_file_to_image(mlx, path, &img.width, &img.height);
	if (img.mlx_img == NULL)
		exit(0);
	img.addr = (t_pixel *)mlx_get_data_addr(img.mlx_img,
			&img.bpp, &img.line_len, &img.endian);
	return (img);
}

int	encode_rgb(uint8_t red, uint8_t green, uint8_t blue)
{
    return (red << 16 | green << 8 | blue);
}

int	main(void)
{
	t_game	game;

	game.mlx_ptr = mlx_init();
	if (game.mlx_ptr == NULL)
		return (MLX_ERROR);
	game.win_ptr = mlx_new_window(game.mlx_ptr, 1000, \
	100, "so_long");
	if (game.win_ptr == NULL)
	{
		free(game.win_ptr);
		return (MLX_ERROR);
	}
	
	render_background(&game, encode_rgb(0, 255, 255));
	load_asset(&game.texture, &game);
	render(&game, 0, 0, game.texture.floor_dirt_1.mlx_img);
	render(&game, 50, 50, game.texture.charac_floor.mlx_img);
	mlx_hook(game.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_loop(game.mlx_ptr);
}