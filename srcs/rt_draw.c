/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:06:03 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/18 00:21:12 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	int	x;
	int	y;
	double	r;
	double	g;
	int	color;

	(void) draw;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r = ((float) x / 1024.0f) * 255.0;
			g = ((float) y / 768.0f) * 255.0;
			color = ((int) r << 16) + ((int) g << 8) + 0;
			my_mlx_pixel_put(data, x, y, color);
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

void	mlx_re_draw(t_handle *handy)
{
	mlx_destroy_image(handy->data.mlx, handy->data.img.img);
	handy->data.img.img = mlx_new_image(handy->data.mlx, WIDTH, HEIGHT);
	handy->data.img.addr = mlx_get_data_addr(handy->data.img.img,
			&handy->data.img.bits_per_pixel, &handy->data.img.line_length,
			&handy->data.img.endian);
	// mlx_clear_window(&handy->data.mlx, &handy->data.win);
	// mlx_draw(&handy->data.img, &handy->draw);
	// mlx_draw2(&handy->data.img, &handy->draw);
	render(handy);
}
