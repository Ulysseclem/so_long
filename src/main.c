/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 11:21:45 by ulysse            #+#    #+#             */
/*   Updated: 2023/06/27 13:04:53 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <mlx.h>

typedef struct s_test
{
	void	*mlx_ptr;
	int width;
	int height;
}	t_test;

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

/* The x and y coordinates of the rect corresponds to its upper left corner. */

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

void	render_background(t_img *img, int color)
{
	int	i;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
	img_pix_put(img, 0, i, color);
	++i;
	}
}



int	render(t_data *data, int i)
{
	i = 0;
	if (data->win_ptr == NULL)
		return (1);
	// render_rect(&data->img, (t_rect){WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100, 100, 100, GREEN_PIXEL});
	// render_rect(&data->img, (t_rect){0, 0, 100, 100, RED_PIXEL});
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 50, 50);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 100, 100);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture.floor.mlx_img, i, 0);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture.floor.mlx_img, 25, 0);

	render_background(&data->texture.charac, WHITE_PIXEL);
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->texture.charac.mlx_img, i, 0);

	return (0);
}

int	handle_keypress(int key, t_data *data)
{
	static int j;

	j = 30;
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (key == XK_a)
	{
		render(data, j);
		j = j + 30;
	}
	return (0);
}

int	main(void)
{
	t_data	data;
	t_test	bou;
	// char	*file;

	// file = open("charac.png", O_RDONLY);
	
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	data.texture.floor.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "Floors.xpm", &bou.width, &bou.height);
	data.texture.charac.mlx_img = mlx_xpm_file_to_image(data.mlx_ptr, "charac.xpm", &bou.width, &bou.height);
	
	// data.texture.floor.addr = mlx_get_data_addr(data.texture.floor.mlx_img, &data.texture.floor.bpp,
	// 		&data.texture.floor.line_len, &data.texture.floor.endian);
	
	data.texture.charac.addr = mlx_get_data_addr(data.texture.charac.mlx_img, &data.texture.charac.bpp,
			&data.texture.charac.line_len, &data.texture.charac.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.texture.floor.mlx_img);
	mlx_destroy_image(data.mlx_ptr, data.texture.charac.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}