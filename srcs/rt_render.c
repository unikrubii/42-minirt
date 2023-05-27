/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/27 02:34:26 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	intersect_put(t_scene *scn, t_handle *handy, t_objbase *p_obj)
{
	t_nml_mat	*vtmp;
	t_lightbase	*p_light;

	p_light = handy->lights;
	while (p_light)
	{
		scn->valid_illum = p_light->light_comp_illum_scn(p_light, \
			handy->objects, p_obj, scn);
		p_light = p_light->next;
	}
	vtmp = nml_mat_sub(scn->v_intpoint, scn->cam_ray->v_point1);
	scn->dist = nml_vect_norm(vtmp);
	if (scn->valid_illum)
		my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
			((int)(p_obj->v_base_color->data[0][0] * scn->intensity) << 16) \
			+ ((int)(p_obj->v_base_color->data[1][0] * scn->intensity) << 8) \
			+ ((int)(p_obj->v_base_color->data[2][0] * scn->intensity)));
	else
		my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
			((int)0 << 16) + ((int)0 << 8) + ((int)0));
	nml_mat_free(vtmp);
}

static void	scene_pixel_put(t_scene *scn, t_handle *handy, t_objbase *p_obj)
{
	while (p_obj)
	{
		scn->valid_inter = p_obj->obj_test_inter_scn(p_obj, scn);
		if (scn->valid_inter)
			intersect_put(scn, handy, p_obj);
		// else
		// 	my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
		// 		((int)0 << 16) + ((int)0 << 8) + ((int)0));
		p_obj = p_obj->next;
	}
}

int	scene_render(t_handle *handy)
{
	t_scene		scn;
	t_objbase	*p_obj;

	scene_init(&scn);
	scn.x = 0;
	while (scn.x < WIDTH)
	{
		scn.y = 0;
		while (scn.y < HEIGHT)
		{
			scn.norm_x = ((float) scn.x * scn.x_fact) - 1.0;
			scn.norm_y = ((float) scn.y * scn.y_fact) - 1.0;
			scn.cam_ray = generate_ray(handy->camera, scn.norm_x, scn.norm_y);
			p_obj = handy->objects;
			scene_pixel_put(&scn, handy, p_obj);
			scn.y++;
			ray_deinit(scn.cam_ray);
		}
		scn.x++;
	}
	// scene_deinit(&scn);
	return (1);
}

int	render(t_handle *handy)
{
	if (handy->data.win == NULL)
		return (1);
	scene_render(handy);
	mlx_put_image_to_window(handy->data.mlx, handy->data.win, \
		handy->data.img.img, 0, 0);
	return (0);
}
