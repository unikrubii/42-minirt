/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:24:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 11:31:05 by nnakarac         ###   ########.fr       */
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
		scn->color = light->v_color;
		scn->intensity = 0.0;
		return (0);
	}
	else
	{
		scn->color = light->v_color;
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
	if (angle > 1.5708)
	{
		scn->color = light->v_color;
		scn->intensity = 0.0;
		return (0);
	}
	else
	{
		scn->color = light->v_color;
		scn->intensity = light->intensity * (1.0 - (angle / 1.5708));
		return (1);
	}
}
