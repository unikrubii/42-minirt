/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/10 20:28:17 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_put(t_scene *scn, t_handle *handy, t_objbase *p_obj)
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
	t_nml_mat	*vtmp;
	t_lightbase	*p_light;
	t_objbase	*closet_obj;

	p_light = handy->lights;
	closet_obj = NULL;
	scn->min_dist = 1e6;
	scn->inter_found = 0;
	scn->valid_inter = 0;
	while (p_obj)
	{
		scn->valid_inter = p_obj->obj_test_inter_scn(p_obj, scn);
		if (scn->valid_inter)
		{
			// compute the flag to indicate that we found an intersection
			scn->inter_found = 1;

			// Compute the distance between the camere and the point of intersection
			vtmp = nml_mat_sub(scn->v_intpoint, scn->cam_ray->v_point1);
			scn->dist = nml_vect_norm(vtmp);
			nml_mat_free(vtmp);
			if (scn->dist <= scn->min_dist)
			{
				scn->min_dist = scn->dist;
				closet_obj = p_obj;
				scn->closet_int_point = nml_mat_cp(scn->v_intpoint);
				scn->closet_lc_normal = nml_mat_cp(scn->v_lc_norm);
				scn->closet_lc_color = nml_mat_cp(scn->v_lc_color);
			}
		}
		p_obj = p_obj->next;
	}

	// Compute the illumination for the closet object, assuming that there was a valid intersection
	if (scn->inter_found)
	{
		if (closet_obj->has_material)
		{
			// Use the material to compute the color
			// compute_color(handy->objects, handy->lights, closet_obj, scn);
			// pix_color_put(scn, handy);
		}
		else
		{
			// compute_diffuse_color(handy->objects, handy->lights, closet_obj, scn);
			// pix_color_put(scn, handy);

			// Compute the intensity of illumination
			scn->red = 0;
			scn->green = 0;
			scn->blue = 0;
			scn->valid_illum = 0;
			scn->illum_found = 0;
			while (p_light)
			{
				scn->valid_illum = p_light->light_comp_illum_scn(p_light, \
					handy->objects, closet_obj, scn);
				if (scn->valid_illum)
				{
					scn->illum_found = 1;

					scn->red += scn->color->data[0][0] * scn->intensity;
					scn->green += scn->color->data[1][0] * scn->intensity;
					scn->blue += scn->color->data[2][0] * scn->intensity;
				}
				p_light = p_light->next;
			}
			if (scn->illum_found)
			{
				scn->red *= scn->closet_lc_color->data[0][0];
				scn->green *= scn->closet_lc_color->data[1][0];
				scn->blue *= scn->closet_lc_color->data[2][0];
				// my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
				// ((int)(scn->red) << 16) \
				// + ((int)(scn->green) << 8) \
				// + ((int)(scn->blue)));
				pix_color_put(scn, handy);
			}
			// else
			// {
			// 	my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
			// 	((int)(0) << 16) \
			// 	+ ((int)(0) << 8) \
			// 	+ ((int)(0)));
			// }
		}


	}
}

// t_ray		*cam_ray;
// 	t_nml_mat	*v_intpoint;
// 	t_nml_mat	*v_lc_norm;
// 	t_nml_mat	*v_lc_color;
// 	float		x_fact;
// 	float		y_fact;
// 	float		min_dist;
// 	float		max_dist;
// 	float		norm_x;
// 	float		norm_y;
// 	int			valid_inter;
// 	float		dist;
// 	float		intensity;
// 	t_nml_mat	*color;
// 	int			valid_illum;
// 	int			x;
// 	int			y;
// 	t_nml_mat	*closet_int_point;
// 	t_nml_mat	*closet_lc_normal;
// 	t_nml_mat	*closet_lc_color;
// 	int			inter_found;
// 	float		red;
// 	float		green;
// 	float		blue;
// 	int			illum_found;

// void	debug_scene_init(t_scene *scn)
// {
// 	scn->x_fact = 1.0 / ((float) WIDTH / 2.0);
// 	scn->y_fact = 1.0 / ((float) HEIGHT / 2.0);
// 	scn->min_dist = 1e6;
// 	scn->max_dist = 0.0;
// 	scn->norm_x = 0.0;
// 	scn->norm_y = 0.0;
// 	scn->cam_ray = NULL;
// 	// scn->bck_ray = NULL;
// 	scn->dist = 0.0;
// 	scn->intensity = 0.0;
// 	scn->red = 0.0;
// 	scn->green = 0.0;
// 	scn->blue = 0.0;
// 	scn->valid_illum = 0;
// 	scn->valid_inter = 0;
// 	scn->illum_found = 0;
// 	scn->inter_found = 0;
// 	scn->closet_int_point = NULL;
// 	scn->closet_lc_color = NULL;
// 	scn->closet_lc_normal = NULL;
// 	scn->color = new_vector();
// 	// scn->v_poi = new_vector();
// 	// scn->v_obj_org = new_vector();
// 	// set_vect(scn->v_obj_org, 0.0, 0.0, 0.0);
// }

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
			if (scn.closet_int_point)
			{
				nml_mat_free(scn.closet_int_point);
				scn.closet_int_point = NULL;
			}
			if (scn.closet_lc_normal)
			{
				nml_mat_free(scn.closet_lc_normal);
				scn.closet_lc_normal = NULL;
			}
			if (scn.closet_lc_color)
			{
				nml_mat_free(scn.closet_lc_color);
				scn.closet_lc_color = NULL;
			}
			scn.cam_ray = generate_ray(handy->camera, scn.norm_x, scn.norm_y);
			p_obj = handy->objects;
			scene_pixel_put(&scn, handy, p_obj);
			scn.y++;
			ray_deinit(scn.cam_ray);
		}
		scn.x++;
	}
	scene_deinit(&scn);
	return (1);
}

int	render(t_handle *handy)
{
	if (handy->data.win == NULL)
		return (1);
	scene_render(handy);
	// remap color of every pixel
	// 1. calculate max value
	// find_max_color(handy);
	opt_color(handy);
	// 2. remap the
	// set_new_color(handy);
	// done
	mlx_put_image_to_window(handy->data.mlx, handy->data.win, \
		handy->data.img.img, 0, 0);
	return (0);
}
