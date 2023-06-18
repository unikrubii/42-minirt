/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blink.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:29:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 16:07:55 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	static t_handle	handy;
	t_camera		cam;
	// t_nml_mat		scr_cen;
	// t_nml_mat		scr_u;
	// t_nml_mat		scr_v;
	// t_objbase		obj_test;

	camera_init(&cam);
	cam_set_pos(&cam, 0.0, -20.0, -5.0);
	cam_set_lookat(&cam, 0.0, 0.0, 0.0);
	cam_set_up(&cam, 0.0, 0.0, 1.0);
	cam_set_length(&cam, 1.0);
	cam_set_hor_size(&cam, (70.0 / 180.0));
	cam_set_aspr(&cam, 16.0 / 9.0);
	update_cam_geomet(&cam);

	// scr_cen = cam_get_scr_cen(&cam);
	// scr_u = cam_get_scr_u(&cam);
	// scr_v = cam_get_scr_v(&cam);

	// printf("scr_cen:\n");
	// vect_print(&scr_cen);
	// printf("scr_u:\n");
	// vect_print(&scr_u);
	// printf("scr_v:\n");
	// vect_print(&scr_v);
	t_matbase mat1, mat2;
	mat1.type = SIM;
	mat_init(&mat1);
	set_vect(mat1.v_base_color, 0.2, 0.8, 0.8);
	mat1.reflectivity = 0.5;
	mat1.shiness = 10.0;

	mat2.type = SIM;
	mat_init(&mat2);
	set_vect(mat2.v_base_color, 0.2, 0.8, 0.8);
	mat2.reflectivity = 0;
	mat2.shiness = 10.0;

	// obj_init(&obj_test, SPH);
	t_fattr	attr, attr2, attr3, attr4, attr5, attr6, attr7;
	attr.v_tr = new_vector();
	attr.v_rot = new_vector();
	attr.v_scl = new_vector();
	attr.v_color = new_vector();
	attr.mat = &mat1;

	attr2.v_tr = new_vector();
	attr2.v_rot = new_vector();
	attr2.v_scl = new_vector();
	attr2.v_color = new_vector();
	attr2.mat = &mat2;

	attr3.v_tr = new_vector();
	attr3.v_rot = new_vector();
	attr3.v_scl = new_vector();
	attr3.v_color = new_vector();
	attr3.mat = &mat1;

	attr4.v_tr = new_vector();
	attr4.v_rot = new_vector();
	attr4.v_scl = new_vector();
	attr4.v_color = new_vector();
	attr4.mat = &mat1;

	attr5.v_tr = new_vector();
	attr5.v_rot = new_vector();
	attr5.v_scl = new_vector();
	attr5.v_color = new_vector();
	attr5.mat = &mat1;

	attr6.v_tr = new_vector();
	attr6.v_rot = new_vector();
	attr6.v_scl = new_vector();
	attr6.v_color = new_vector();
	attr6.mat = &mat1;

	attr7.v_tr = new_vector();
	attr7.v_rot = new_vector();
	attr7.v_scl = new_vector();
	attr7.v_color = new_vector();
	attr7.mat = NULL;

	set_vect(attr.v_tr, -1.5, 1.5, 0.0);
	set_vect(attr.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr.v_scl, 1, 1, 1);
	set_vect(attr.v_color, 1.0, 1.0, 1.0);

	set_vect(attr2.v_tr, 0.0, -1.0, 0.0);
	set_vect(attr2.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr2.v_scl, 0.5, 0.5, 0.5);
	set_vect(attr2.v_color, 0.52, 0.33, 0.18);

	set_vect(attr3.v_tr, 1.5, -1.0, 0.0);
	set_vect(attr3.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr3.v_scl, 0.5, 0.5, 0.5);
	set_vect(attr3.v_color, 1.0, 1.0, 1.0);

	set_vect(attr7.v_tr, 1.5, -1.0, -0.5);
	set_vect(attr7.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr7.v_scl, 0.5, 0.5, 0.5);
	set_vect(attr7.v_color, 0.2, 0.2, 0.2);

	set_vect(attr4.v_tr, 0.0, 0.0, 2);
	set_vect(attr4.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr4.v_scl, 40, 40, 40);
	set_vect(attr4.v_color, 1.0, 1.0, 1.0);

	set_vect(attr5.v_tr, 0.0, 0.0, -3.25);
	set_vect(attr5.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr5.v_scl, 10, 10, 10);
	set_vect(attr5.v_color, 1.0, 1.0, 1.0);

	// set_vect(attr6.v_tr, 0.0, 0.0, 0.0);
	// set_vect(attr6.v_rot, PI/2, 0.0, 0.0);
	// set_vect(attr6.v_scl, 500, 500, 500);
	// set_vect(attr6.v_color, 1.0, 1.0, 1.0);

	objlst_add_back(&handy.objects, objlst_new(SPH, &attr, 1));
	// objlst_add_back(&handy.objects, objlst_new(SPH, &attr3, 2));
	// objlst_add_back(&handy.objects, objlst_new(SPH, &attr2, 3));
	// objlst_add_back(&handy.objects, objlst_new(SPH, &attr7, 3));
	objlst_add_back(&handy.objects, objlst_new(PLN, &attr4, 4));
	// objlst_add_back(&handy.objects, objlst_new(PLN, &attr5, 5));
	// objlst_add_back(&handy.objects, objlst_new(PLN, &attr6, 6));
	lightlst_add_back(&handy.lights, lightlst_new(PNT));
	lightlst_add_back(&handy.lights, lightlst_new(PNT));
	// lightlst_add_back(&handy.lights, lightlst_new(PNT));
	set_vect(handy.lights->v_location, -5.0, -10.0, -2.0);
	set_vect(handy.lights->v_color, 255.0, 255.0, 255.0);
	set_vect(handy.lights->next->v_location, 5.0, -10.0, -2.0);
	set_vect(handy.lights->next->v_color, 255.0, 255.0, 255.0);
	// set_vect(handy.lights->next->next->v_location, 0.0, 0.0, -4.0);
	// set_vect(handy.lights->next->next->v_color, 255.0, 255.0, 255.0);
	init_color_pix(&handy);

	handy.camera = &cam;
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
	// mlx_re_draw(&handy);
	mlx_loop(handy.data.mlx);

	// deinit_color_pix(&handy);
	// objlst_clear(&(handy.objects));
	// lightlst_clear(&(handy.lights));
	// camera_deinit(&cam);
	// mat_deinit(&mat1);
	// mat_deinit(&mat2);
	return (0);
}
