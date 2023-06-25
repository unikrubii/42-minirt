/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlightutil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:03:44 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 20:09:28 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "lightbase.h"

int	validint_util(int valid_int, t_scene *shadow_scn, t_scene *scn)
{
	float		dist;
	t_nml_mat	*vtmp;

	dist = 0.0f;
	if (valid_int)
	{
		vtmp = nml_mat_sub(shadow_scn->v_intpoint, \
			scn->closet_int_point);
		dist = nml_vect_norm(vtmp);
		nml_mat_free(vtmp);
		if (dist > scn->tmp_light_dist)
			valid_int = 0;
	}
	return (valid_int);
}

int	p_light_comp_illum_scn_close_validint(t_objbase *obj, t_objbase *cur_obj, \
	t_scene *shadow_scn, t_scene *scn)
{
	int			valid_int;
	t_objbase	*p_obj;

	p_obj = obj;
	valid_int = 0;
	while (p_obj)
	{
		if (p_obj->id != cur_obj->id)
		{
			valid_int = p_obj->obj_test_inter_scn(p_obj, shadow_scn);
			valid_int = validint_util(valid_int, shadow_scn, scn);
		}
		if (valid_int)
			break ;
		p_obj = p_obj->next;
	}
	return (valid_int);
}

int	p_light_comp_illum_scn_close_validate(int valid_int, t_scene *scn, \
	t_lightbase *light, t_nml_mat *v_light_dir)
{
	float		angle;

	angle = 0.0;
	if (!valid_int)
	{
		angle = acos(nml_vect_dot(scn->closet_lc_normal, 0, v_light_dir, 0));
		if (angle > 1.57079634)
		{
			scn->intensity = 0.0;
			return (set_vect_from_vect(light->v_color, scn->color), 0);
		}
		else
		{
			set_vect_from_vect(light->v_color, scn->color);
			scn->intensity = light->intensity * (1.0 - (angle / 1.57079634));
			return (set_vect_from_vect(light->v_color, scn->color), 1);
		}
	}
	else
	{
		scn->intensity = 0.0;
		return (set_vect_from_vect(light->v_color, scn->color), 0);
	}
}

int	p_light_comp_illum_scn_close(t_lightbase *light, \
	t_objbase *obj, t_objbase *cur_obj, t_scene *scn)
{
	t_nml_mat	*v_light_dir;
	t_nml_mat	*start_point;
	t_nml_mat	*v_tmp;
	t_ray		*light_ray;
	t_scene		shd_scn;

	light_ray = malloc(sizeof(t_ray));
	start_point = nml_mat_cp(scn->closet_int_point);
	v_light_dir = nml_mat_sub(light->v_location, scn->closet_int_point);
	nml_vect_normalize_r(v_light_dir);
	v_tmp = nml_mat_add(start_point, v_light_dir);
	ray_init(light_ray, start_point, v_tmp);
	nml_mat_free(v_tmp);
	scene_init(&shd_scn);
	shd_scn.x = scn->x;
	shd_scn.y = scn->y;
	shd_scn.norm_x = ((float) shd_scn.x * shd_scn.x_fact) - 1.0;
	shd_scn.norm_y = ((float) shd_scn.y * shd_scn.y_fact) - 1.0;
	shd_scn.cam_ray = light_ray;
	return (p_light_comp_illum_scn_close_validate(\
		p_light_comp_illum_scn_close_validint(obj, cur_obj, &shd_scn, scn), \
		scn, light, v_light_dir));
}
