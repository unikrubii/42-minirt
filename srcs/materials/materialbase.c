/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materialbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:54:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/11 22:59:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

void	mat_init(t_matbase *mat)
{
	(void) mat;
	mat->v_base_color = new_vector();
	set_vect(mat->v_base_color, 1.0, 0.0, 1.0);
	mat->shiness = 0.0;
	mat->reflectivity = 0.0;
}

void	mat_deinit(t_matbase *mat)
{
	(void) mat;
	nml_mat_free(mat->v_base_color);
}

// function to compute the color of the material
void	compute_color(t_handle *handy, t_objbase *closet_obj, t_scene *scn)
{
	(void) handy;
	(void) closet_obj;
	(void) scn;
	// Define an initial material color
}

void	compute_diffuse_color(t_handle *handy, t_objbase *closet_obj, t_scene *scn)
{
	t_lightbase	*p_light;

	// Compute the color dur to diffuse illumination
	scn->red = 0;
	scn->green = 0;
	scn->blue = 0;
	scn->valid_illum = 0;
	scn->illum_found = 0;
	p_light = handy->lights;
	while (p_light)
	{
		scn->valid_illum = p_light->light_comp_illum_scn(p_light, handy->objects, closet_obj, scn);
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
		set_vect(scn->dif_color, scn->red, scn->green, scn->blue);
	}
}

int	cast_ray(t_scene *scn, t_handle *handy, t_objbase *this_obj, t_objbase **closet_obj)
{
	t_objbase	*p_obj;
	t_nml_mat	*v_tmp;

	scn->min_dist = 1e6;
	scn->v_intpoint = new_vector();
	scn->v_lc_norm = new_vector();
	scn->v_lc_color = new_vector();
	scn->inter_found = 0;
	p_obj = handy->objects;
	while (p_obj)
	{
		if (p_obj != this_obj)
		{
			scn->valid_inter = p_obj->obj_test_inter_scn(p_obj, scn);
			if (scn->valid_inter)
			{
				scn->inter_found = 1;
				v_tmp = nml_mat_sub(scn->v_intpoint, scn->cam_ray->v_point1);
				scn->dist = nml_vect_norm(v_tmp);
				nml_mat_free(v_tmp);
				if (scn->dist <= scn->min_dist)
				{
					*closet_obj = p_obj;
					// set_vect_from_vect(scn->v_intpoint, scn->closet_int_point);
					// set_vect_from_vect(scn->v_lc_norm, scn->closet_lc_normal);
					// set_vect_from_vect(scn->v_lc_color, scn->closet_lc_color);
					scn->closet_int_point = nml_mat_cp(scn->v_intpoint);
					scn->closet_lc_normal = nml_mat_cp(scn->v_lc_norm);
					scn->closet_lc_color = nml_mat_cp(scn->v_lc_color);
				}
			}
		}
		p_obj = p_obj->next;
	}
	return (scn->inter_found);
}

// function to compute the reflection color
void	compute_reflect_color(t_handle *handy, t_objbase *obj, t_scene *scn)
{
	t_nml_mat	*d;
	t_nml_mat	*v_rfl;
	t_nml_mat	*v_tmp;

	t_ray		*rfl_ray;

	t_objbase	*closet_obj;
	t_scene		rfl_scn;

	(void) handy;
	(void) obj;
	(void) scn;
	closet_obj = NULL;
	rfl_ray = malloc(sizeof(t_ray));
	d = new_vector();
	d = nml_mat_cp(scn->cam_ray->v_lab);
	v_tmp = nml_mat_smult(scn->v_lc_norm, 2 * nml_vect_dot(d, 0, scn->v_lc_norm, 0));
	v_rfl = nml_mat_sub(d, v_tmp);
	nml_mat_free(v_tmp);

	v_tmp = nml_mat_add(scn->v_intpoint, v_rfl);
	// construct the reflection ray.
	ray_init(rfl_ray, scn->v_intpoint, v_tmp);
	nml_mat_free(v_tmp);
	scene_init(&rfl_scn);
	rfl_scn.v_intpoint = new_vector();
	rfl_scn.v_lc_norm = new_vector();
	rfl_scn.color = new_vector();
	rfl_scn.x = scn->x;
	rfl_scn.y = scn->y;
	rfl_scn.norm_x = ((float) rfl_scn.x * rfl_scn.x_fact) - 1.0;
	rfl_scn.norm_y = ((float) rfl_scn.y * rfl_scn.y_fact) - 1.0;
	rfl_scn.red = 0.0;
	rfl_scn.green = 0.0;
	rfl_scn.blue = 0.0;
	rfl_scn.intensity = 0.0;
	rfl_scn.cam_ray = rfl_ray;
	// Cast this ray into the scene and find the closet object that it intersects with
	rfl_scn.inter_found = cast_ray(&rfl_scn, handy, obj, &closet_obj);
	if ((rfl_scn.inter_found) && (handy->rfl_ray_cnt < handy->max_rfl_ray))
	{
		handy->max_rfl_ray++;
		if (closet_obj->has_material)
		{
			if (closet_obj->material->type == SIM)
				simple_compute_color(handy, closet_obj, &rfl_scn);
		}
		else
		{
			compute_diffuse_color(handy, closet_obj, &rfl_scn);
		}
	}
	set_vect_from_vect(rfl_scn.mat_color, scn->ref_color);
}
