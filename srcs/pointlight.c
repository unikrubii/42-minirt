/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:24:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 18:52:52 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "lightbase.h"

void	p_light_init(t_lightbase *light)
{
	// set_vect(light->v_color, 1.0, 1.0, 1.0);
	light->intensity = 1.0;
}

void	p_light_deinit(t_lightbase *light)
{
	(void) light;
}

// int		p_light_comp_illum(t_lightbase *light,
// 		t_nml_mat *intpoint,
// 		t_nml_mat *lc_normal, t_objbase *obj,
// 		t_objbase *cur_obj, t_nml_mat *color,
// 		float *intensity)
// {
// 	t_nml_mat	*v_light_dir;
// 	t_nml_mat	*v_start_point;

// 	float		angle;

// 	(void) obj;
// 	(void) cur_obj;
// 	// Construct a vector pointing from the intersection point to the light.
// 	v_light_dir = nml_mat_sub(light->v_location, intpoint);
// 	nml_vect_normalize_r(v_light_dir);

// 	// Compute a starting point
// 	v_start_point = nml_mat_cp(intpoint);

// 	// Compute the angle between the local normal and the light ray.
// 	// Note that we assume the localNormal is a unit vector
// 	angle = acos(nml_vect_dot(lc_normal, 0, v_light_dir, 0));

// 	// If the normal is pointing away from the light,
// 	// then we have no illumination.
// 	if (angle > 1.5708)
// 	{
// 		// No illimination
// 		color = light->v_color;
// 		*intensity = 0.0;
// 		return (0);
// 	}
// 	else
// 	{
// 		color = light->v_color;
// 		*intensity = light->intensity * (1.0 - (angle / 1.5708));
// 		return (1);
// 	}
// }

int	p_light_comp_illum_scn(t_lightbase *light, \
	t_objbase *obj, t_objbase *cur_obj, t_scene *scn)
{
	t_nml_mat	*v_light_dir;
	float		angle;

	(void) obj;
	(void) cur_obj;
	v_light_dir = nml_mat_sub(light->v_location, scn->v_intpoint);
	nml_vect_normalize_r(v_light_dir);
	angle = acos(nml_vect_dot(scn->v_lc_norm, 0, v_light_dir, 0));
	if (angle > 1.5708)
	{
		// scn->color = light->v_color;
		set_vect(scn->color, light->v_color->data[0][0], light->v_color->data[1][0], light->v_color->data[2][0]);
		scn->intensity = 0.0;
		return (0);
	}
	else
	{
		// scn->color = light->v_color;
		set_vect(scn->color, light->v_color->data[0][0], light->v_color->data[1][0], light->v_color->data[2][0]);
		scn->intensity = light->intensity * (1.0 - (angle / 1.5708));
		return (1);
	}
}

int	p_light_comp_illum_scn_close(t_lightbase *light, \
	t_objbase *obj, t_objbase *cur_obj, t_scene *scn)
{
	t_nml_mat	*v_light_dir;
	float		angle;

	(void) obj;
	(void) cur_obj;
	v_light_dir = nml_mat_sub(light->v_location, scn->closet_int_point);
	nml_vect_normalize_r(v_light_dir);
	angle = acos(nml_vect_dot(scn->closet_lc_normal, 0, v_light_dir, 0));
	if (angle > 1.57079634)
	{
		// scn->color = light->v_color;
		set_vect(scn->color, light->v_color->data[0][0], light->v_color->data[1][0], light->v_color->data[2][0]);
		scn->intensity = 0.0;
		return (0);
	}
	else
	{
		set_vect(scn->color, light->v_color->data[0][0], light->v_color->data[1][0], light->v_color->data[2][0]);
		scn->intensity = light->intensity * (1.0 - (angle / 1.57079634));
		// scn->intensity = 1.0;
		// if (scn->debug)
		// {
		// 	// printf("intense: %f\n", scn->intensity);
		// 	set_vect(scn->color, 255, 0, 0);
		// 	scn->debug = 0;
		// }
		return (1);
	}
}
