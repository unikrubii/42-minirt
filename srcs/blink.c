/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blink.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:29:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/07 20:22:32 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	static t_handle	handy;
	t_camera		cam;
	t_nml_mat		scr_cen;
	t_nml_mat		scr_u;
	t_nml_mat		scr_v;
	// t_objbase		obj_test;

	camera_init(&cam);
	cam_set_pos(&cam, 0.0, -10.0, 0.0);
	cam_set_lookat(&cam, 0.0, 0.0, 0.0);
	cam_set_up(&cam, 0.0, 0.0, 1.0);
	cam_set_length(&cam, 1.0);
	cam_set_hor_size(&cam, 0.25);
	cam_set_aspr(&cam, 16.0 / 9.0);
	update_cam_geomet(&cam);

	scr_cen = cam_get_scr_cen(&cam);
	scr_u = cam_get_scr_u(&cam);
	scr_v = cam_get_scr_v(&cam);

	printf("scr_cen:\n");
	vect_print(&scr_cen);
	printf("scr_u:\n");
	vect_print(&scr_u);
	printf("scr_v:\n");
	vect_print(&scr_v);

	// obj_init(&obj_test, SPH);

	objlst_add_back(&handy.objects, objlst_new(SPH));

	handy.camera = &cam;
	// handy.objects = &obj_test;
	handy.to_render = 1;

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
	return (0);
}
