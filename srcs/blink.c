/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blink.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:29:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/24 17:51:36 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	static t_handle	handy;

	read_map(argc, argv, &handy);
	// handy.objects = &obj_test;
	handy.to_render = 1;

	handy.max_rfl_ray = 3;
	handy.rfl_ray_cnt = 0;

	handy.data.mlx = mlx_init();
	handy.data.win = mlx_new_window(handy.data.mlx, WIDTH, HEIGHT, "RT");
	handy.data.img.img = mlx_new_image(handy.data.mlx, WIDTH, HEIGHT);
	handy.data.img.addr = mlx_get_data_addr(handy.data.img.img, \
		&handy.data.img.bits_per_pixel, &handy.data.img.line_length, \
		&handy.data.img.endian);
	mlx_hook(handy.data.win, ON_DESTROY, 1L << 0, mlx_close, &handy);
	mlx_hook(handy.data.win, ON_KEYDOWN, 1L << 0, rt_key_handler, &handy);
	// render(&handy);
	mlx_loop_hook(handy.data.mlx, &mlx_re_draw, &handy);
	mlx_loop(handy.data.mlx);

	// deinit_color_pix(&handy);
	// objlst_clear(&(handy.objects));
	// lightlst_clear(&(handy.lights));
	// camera_deinit(&cam);
	// mat_deinit(&mat1);
	// mat_deinit(&mat2);
	return (0);
}
