/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blink.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:29:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/17 22:03:56 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	static t_handle	handy;

	handy.data.mlx = mlx_init();
	handy.data.win = mlx_new_window(handy.data.mlx, WIDTH, HEIGHT, "RT");
	handy.data.img.img = mlx_new_image(handy.data.mlx, WIDTH, HEIGHT);
	handy.data.img.addr = mlx_get_data_addr(handy.data.img.img, \
		&handy.data.img.bits_per_pixel, &handy.data.img.line_length, \
		&handy.data.img.endian);
	mlx_hook(handy.data.win, ON_DESTROY, 1L << 0, mlx_close, &handy.data);
	mlx_hook(handy.data.win, ON_KEYDOWN, 1L << 0, rt_key_handler, &handy);
	mlx_loop_hook(handy.data.mlx, &render, &handy.data);
	mlx_loop(handy.data.mlx);
	return (0);
}
