/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:06:03 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 14:24:02 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief put color into each pixels
/// @param data screen pixels pointer
/// @param x horizontal coordinade
/// @param y vertical coordinate
/// @param color rgb color
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

/// @brief receive and convert color into the right endian format
/// return input if little endian
/// @param color color in ARGB format
/// @return
int	mlx_conv_color(int color)
{
	int	r;
	int	g;
	int	b;
	int	a;

	if (endian())
	{
		a = (color >> 24) & 0xFF;
		r = (color >> 16) & 0xFF;
		g = (color >> 8) & 0xFF;
		b = color & 0xFF;
		return ((r << 24) + (g << 16) + (b << 8) + a);
	}
	return (color);
}

void	mlx_draw(t_data *data, t_draw *draw)
{
	int		x;
	int		y;
	float	r;
	float	g;

	(void) draw;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r = ((float) x / WIDTH) * 255.0;
			g = ((float) y / HEIGHT) * 255.0;
			my_mlx_pixel_put(data, x, y, ((int) r << 16) + ((int) g << 8));
			x++;
		}
		y++;
	}
}

void	mlx_draw2(t_data *data, t_draw *draw)
{
	int	x;
	int	y;

	(void) draw;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(data, x, y, 0xF00000FF);
			x++;
		}
		y++;
	}
}

/// @brief function to re draw the whole image
/// @param handy main struct ptr
/// @return
int	mlx_re_draw(t_handle *handy)
{
	if (handy->to_render)
	{
		mlx_destroy_image(handy->data.mlx, handy->data.img.img);
		handy->data.img.img = mlx_new_image(handy->data.mlx, WIDTH, HEIGHT);
		handy->data.img.addr = mlx_get_data_addr(handy->data.img.img,
				&handy->data.img.bits_per_pixel, &handy->data.img.line_length,
				&handy->data.img.endian);
		render(handy);
		handy->to_render = 0;
	}
	return (1);
}
