/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blink.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:29:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 12:27:13 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_color_pix(t_handle *handy)
{
	int			width;
	int			height;
	t_nml_mat	**dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	width = 0;
	height = 0;
	// init all pixel color
	handy->vv_color = malloc(sizeof(t_nml_mat *) * WIDTH * HEIGHT);
	while (width < WIDTH)
	{
		height = 0;
		while (height < HEIGHT)
		{
			dst = handy->vv_color + (HEIGHT * width) + (height);
			*dst = new_vector();
			height++;
		}
		width++;
	}
}

void	clear_attr(t_fattr *attr)
{
	nml_mat_free(attr->v_color);
	nml_mat_free(attr->v_rot);
	nml_mat_free(attr->v_scl);
	nml_mat_free(attr->v_tr);
}

int	main(void)
{
	static t_handle	handy;
	t_camera		cam;
	t_nml_mat		scr_cen;
	t_nml_mat		scr_u;
	t_nml_mat		scr_v;
	// t_objbase		obj_test;

	camera_init(&cam);
	cam_set_pos(&cam, 0.0, -10.0, -1.0);
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
	t_fattr	attr, attr2, attr3, attr4;
	attr.v_tr = new_vector();
	attr.v_rot = new_vector();
	attr.v_scl = new_vector();
	attr.v_color = new_vector();

	attr2.v_tr = new_vector();
	attr2.v_rot = new_vector();
	attr2.v_scl = new_vector();
	attr2.v_color = new_vector();

	attr3.v_tr = new_vector();
	attr3.v_rot = new_vector();
	attr3.v_scl = new_vector();
	attr3.v_color = new_vector();

	attr4.v_tr = new_vector();
	attr4.v_rot = new_vector();
	attr4.v_scl = new_vector();
	attr4.v_color = new_vector();

	set_vect(attr.v_tr, -1.5, 0.0, 0.0);
	set_vect(attr.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr.v_scl, 0.5, 0.5, 0.75);
	set_vect(attr.v_color, 1, 0.0, 0.0);

	set_vect(attr2.v_tr, 0.0, 0.0, 0.0);
	set_vect(attr2.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr2.v_scl, 0.5, 0.5, 0.5);
	set_vect(attr2.v_color, 0.5, 1, 0.5);

	set_vect(attr3.v_tr, 0.5, 0.0, 0.0);
	set_vect(attr3.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr3.v_scl, 0.5, 0.5, 0.5);
	set_vect(attr3.v_color, 0.0, 0.0, 1);

	set_vect(attr4.v_tr, 0.0, 0.0, 0.75);
	set_vect(attr4.v_rot, 0.0, 0.0, 0.0);
	set_vect(attr4.v_scl, 4, 4, 1);
	set_vect(attr4.v_color, 0.5, 0.5, 0.5);

	// objlst_add_back(&handy.objects, objlst_new(SPH, &attr));
	objlst_add_back(&handy.objects, objlst_new(SPH, &attr2));
	// objlst_add_back(&handy.objects, objlst_new(SPH, &attr3));
	// objlst_add_back(&handy.objects, objlst_new(PLN, &attr4));
	lightlst_add_back(&handy.lights, lightlst_new(PNT));
	set_vect(handy.lights->v_location, 5.0, -20.0, -5.0);
	set_vect(handy.lights->v_color, 255.0, 255.0, 255.0);

	clear_attr(&attr);
	clear_attr(&attr2);
	clear_attr(&attr3);
	clear_attr(&attr4);

	handy.camera = &cam;
	// handy.objects = &obj_test;
	handy.to_render = 1;

	init_color_pix(&handy);
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
