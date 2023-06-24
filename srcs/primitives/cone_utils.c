/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 04:21:20 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	cone_close_enough(t_inter_calc *cone)
{
	if (obj_close_enough(cone->vhat->data[2][0], 0.0))
	{
		cone->t3_valid = 0;
		cone->tt[2] = 100e6;
	}
	else
	{
		cone->tt[2] = (cone->bck_ray->v_point1->data[2][0] - 1.0) / \
			-cone->vhat->data[2][0];
		cone->poi[2] = nml_mat_add(cone->bck_ray->v_point1, \
			nml_mat_smult(cone->vhat, cone->tt[2]));
		if ((cone->tt[2] > 0.0) && (sqrtf(powf(cone->poi[2]->data[0][0], 2.0) \
			+ powf(cone->poi[2]->data[1][0], 2.0)) < 1.0))
			cone->t3_valid = 1;
		else
		{
			cone->t3_valid = 0;
			cone->tt[2] = 100e6;
		}
	}
}

void	cone_get_min(t_inter_calc *cone)
{
	int	i;

	cone->min_i = 0;
	cone->min_t = 10e6;
	i = 0;
	while (i < 3)
	{
		if (cone->tt[i] < cone->min_t)
		{
			cone->min_t = cone->tt[i];
			cone->min_i = i;
		}
		i++;
	}
}

int	cone_not_side_inter(t_objbase *obj, t_scene *scn, t_inter_calc *cone)
{
	if (!obj_close_enough(cone->vhat->data[2][0], 0.0))
	{
		if (sqrtf(powf(cone->valid_poi->data[0][0], 2.0) + \
			powf(cone->valid_poi->data[1][0], 2.0)) < 1.0)
		{
			set_vect(cone->org_normal, 0.0, 0.0, 1.0);
			scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, \
				cone->org_normal, FWDFM), cone->global_origin);
			nml_mat_normalize_r(scn->v_lc_norm);
			scn->v_lc_color = nml_mat_cp(obj->v_base_color);
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}

int	cone_side_inter(t_objbase *obj, t_scene *scn, t_inter_calc *cone)
{
	cone->valid_poi = nml_mat_cp(cone->poi[cone->min_i]);
	cone->local_origin = new_vector();
	set_vect(cone->local_origin, 0.0, 0.0, 0.0);
	cone->global_origin = new_vector();
	cone->org_normal = new_vector();
	scn->v_intpoint = gt_apply(obj->transmat, cone->valid_poi, FWDFM);
	cone->global_origin = gt_apply(obj->transmat, cone->local_origin, FWDFM);
	if (cone->min_i < 2)
	{
		cone->tx = cone->valid_poi->data[0][0];
		cone->ty = cone->valid_poi->data[1][0];
		cone->tz = -sqrtf(powf(cone->tx, 2.0) + powf(cone->ty, 2.0));
		set_vect(cone->org_normal, cone->tx, cone->ty, cone->tz);
		scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, \
			cone->org_normal, FWDFM), cone->global_origin);
		nml_mat_normalize_r(scn->v_lc_norm);
		scn->v_lc_color = nml_mat_cp(obj->v_base_color);
		return (1);
	}
	else
		return (cone_not_side_inter(obj, scn, cone));
	return (0);
}
