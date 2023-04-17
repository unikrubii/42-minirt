/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:06:03 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/12 19:10:22 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

void	mlx_draw(t_data *data, t_draw *draw)
{

}

void	mlx_re_draw(t_handle *handy)
{
	mlx_destroy_image(handy->data->mlx, handy->data->img.img);
	handy->data->img.img = mlx_new_image(handy->data->mlx, WIDTH, HEIGHT);
	handy->data->img.addr = mlx_get_data_addr(handy->data->img.img,
			&handy->data->img.bits_per_pixel, &handy->data->img.line_length,
			&handy->data->img.endian);
	mlx_clear_window(handy->data->mlx, handy->data->win);
	// mlx_draw(handy->data, handy->draw);
}
