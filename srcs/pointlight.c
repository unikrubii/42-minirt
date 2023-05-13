/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:24:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/13 11:52:22 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "lightbase.h"

void	p_light_init(t_lightbase *light)
{
	set_vect(light->v_color, 1.0, 1.0, 1.0);
	light->intensity = 1.0;
}

void	p_light_deinit(t_lightbase *light)
{
	(void) light;
}

int		p_light_comp_illum(t_lightbase *light, t_nml_mat *intpoint, \
		t_nml_mat *lc_normal, t_objbase *obj, \
		t_objbase *cur_obj, t_nml_mat *color, \
		float *intensity)
{
	t_nml_mat	*v_light_dir;
	t_nml_mat	*v_start_point;

	float		angle;

	(void) obj;
	(void) cur_obj;
	// Construct a vector pointing from the intersection point to the light.
	v_light_dir = nml_mat_sub(light->v_location, intpoint);
	nml_vect_normalize_r(v_light_dir);

	// Compute a starting point
	v_start_point = nml_mat_cp(intpoint);

	// Compute the angle between the local normal and the light ray.
	// Note that we assume the localNormal is a unit vector
	angle = acos(nml_vect_dot(lc_normal, 0, v_light_dir, 0));

	// If the normal is pointing away from the light, then we have no illumination.
	if (angle > 1.5708)
	{
		// No illimination
		color = light->v_color;
		*intensity = 0.0;
		return (0);
	}
	else
	{
		color = light->v_color;
		*intensity = light->intensity * (1.0 - (angle / 1.5708));
		return (1);
	}
}
