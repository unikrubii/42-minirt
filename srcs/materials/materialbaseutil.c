/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materialbaseutil.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 01:04:55 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/24 13:42:00 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

void	cast_ray_util(t_scene *scn, t_objbase *p_obj, t_objbase **closet_obj)
{
	t_nml_mat	*v_tmp;

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
			scn->closet_int_point = nml_mat_cp(scn->v_intpoint);
			scn->closet_lc_normal = nml_mat_cp(scn->v_lc_norm);
			scn->closet_lc_color = nml_mat_cp(scn->v_lc_color);
		}
	}
}

/// @brief cast ray function
/// @param scn
/// @param handy
/// @param this_obj
/// @param closet_obj
/// @return
int	cast_ray(t_scene *scn, t_handle *handy, t_objbase *this_obj, \
	t_objbase **closet_obj)
{
	t_objbase	*p_obj;

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
			cast_ray_util(scn, p_obj, closet_obj);
		}
		p_obj = p_obj->next;
	}
	return (scn->inter_found);
}

/// @brief utility to compute the reflection color
/// @param handy
/// @param obj
/// @param closet_obj
/// @param rfl_scn
void	compute_reflect_color_util(t_handle *handy, t_objbase *obj, \
	t_objbase **closet_obj, t_scene *rfl_scn)
{
	rfl_scn->inter_found = cast_ray(rfl_scn, handy, obj, closet_obj);
	if ((rfl_scn->inter_found) && (handy->rfl_ray_cnt < handy->max_rfl_ray))
	{
		handy->max_rfl_ray++;
		if ((*closet_obj)->has_material)
		{
			if ((*closet_obj)->material->type == SIM)
				simple_compute_color(handy, *closet_obj, rfl_scn);
		}
		else
		{
			compute_diffuse_color(handy, *closet_obj, rfl_scn);
		}
	}
}

/// @brief function to compute the reflection color
/// @param handy
/// @param obj
/// @param scn
/// @param rfl_scn
void	compute_reflect_color(t_handle *handy, t_objbase *obj, t_scene *scn, \
	t_scene *rfl_scn)
{
	t_nml_mat	*d;
	t_nml_mat	*v_rfl;
	t_nml_mat	*v_tmp;
	t_ray		*rfl_ray;
	t_objbase	*closet_obj;

	closet_obj = NULL;
	rfl_ray = malloc(sizeof(t_ray));
	d = new_vector();
	d = nml_mat_cp(scn->cam_ray->v_lab);
	v_tmp = nml_mat_smult(scn->v_lc_norm, 2 * \
		nml_vect_dot(d, 0, scn->v_lc_norm, 0));
	v_rfl = nml_mat_sub(d, v_tmp);
	nml_mat_free(v_tmp);
	v_tmp = nml_mat_add(scn->v_intpoint, v_rfl);
	ray_init(rfl_ray, scn->v_intpoint, v_tmp);
	nml_mat_free(v_tmp);
	rfl_scn->x = scn->x;
	rfl_scn->y = scn->y;
	rfl_scn->norm_x = ((float) rfl_scn->x * rfl_scn->x_fact) - 1.0;
	rfl_scn->norm_y = ((float) rfl_scn->y * rfl_scn->y_fact) - 1.0;
	rfl_scn->cam_ray = rfl_ray;
	compute_reflect_color_util(handy, obj, &closet_obj, rfl_scn);
	set_vect_from_vect(rfl_scn->mat_color, scn->ref_color);
}
