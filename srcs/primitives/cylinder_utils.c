/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 04:53:47 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	cyl_not_close_enough(t_inter_calc *cyl)
{
	cyl->tt[2] = (cyl->bck_ray->v_point1->data[2][0] - 1.0) / \
		-cyl->vhat->data[2][0];
	cyl->tt[3] = (cyl->bck_ray->v_point1->data[2][0] + 1.0) / \
		-cyl->vhat->data[2][0];
	cyl->poi[2] = nml_mat_add(cyl->bck_ray->v_point1, \
		nml_mat_smult(cyl->vhat, cyl->tt[2]));
	cyl->poi[3] = nml_mat_add(cyl->bck_ray->v_point1, \
		nml_mat_smult(cyl->vhat, cyl->tt[3]));
	if ((cyl->tt[2] > 0.0) && sqrtf(powf(cyl->poi[2]->data[0][0], 2)) + \
		powf(cyl->poi[2]->data[1][0], 2) < 1.0)
		cyl->t3_valid = 1;
	else
	{
		cyl->t3_valid = 0;
		cyl->tt[2] = 100e6;
	}
	if ((cyl->tt[3] > 0.0) && sqrtf(powf(cyl->poi[3]->data[0][0], 2)) + \
		powf(cyl->poi[3]->data[1][0], 2) < 1.0)
		cyl->t4_valid = 1;
	else
	{
		cyl->t4_valid = 0;
		cyl->tt[3] = 100e6;
	}
}

void	cyl_close_enough(t_inter_calc *cyl)
{
	if (obj_close_enough(cyl->vhat->data[2][0], 0.0))
	{
		cyl->t3_valid = 0;
		cyl->t4_valid = 0;
		cyl->tt[2] = 100e6;
		cyl->tt[3] = 100e6;
	}
	else
		cyl_not_close_enough(cyl);
}

void	cyl_get_min(t_inter_calc *cyl)
{
	int		i;

	cyl->min_i = 0;
	cyl->min_t = 10e6;
	i = 0;
	while (i < 4)
	{
		if (cyl->tt[i] < cyl->min_t)
		{
			cyl->min_t = cyl->tt[i];
			cyl->min_i = i;
		}
		i++;
	}
}

int	cyl_not_side_inter(t_objbase *obj, t_scene *scn, t_inter_calc *cyl)
{
	if (!obj_close_enough(cyl->vhat->data[2][0], 0.0))
	{
		if (sqrtf(pow(cyl->valid_poi->data[0][0], 2) + \
			pow(cyl->valid_poi->data[1][0], 2)) < 1.0)
		{
			scn->v_intpoint = gt_apply(obj->transmat, cyl->valid_poi, FWDFM);
			set_vect(cyl->org_normal, obj->up_x, obj->up_y, obj->up_z + \
				cyl->valid_poi->data[2][0]);
			cyl->global_origin = gt_apply(obj->transmat, \
				cyl->local_origin, FWDFM);
			scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, \
				cyl->org_normal, FWDFM), cyl->global_origin);
			nml_mat_normalize_r(scn->v_lc_norm);
			scn->v_lc_color = nml_mat_cp(obj->v_base_color);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	cyl_side_inter(t_objbase *obj, t_scene *scn, t_inter_calc *cyl)
{
	cyl->local_origin = new_vector();
	set_vect(cyl->local_origin, 0.0, 0.0, 0.0);
	cyl->org_normal = new_vector();
	cyl->valid_poi = nml_mat_cp(cyl->poi[cyl->min_i]);
	if (cyl->min_i < 2)
	{
		scn->v_intpoint = gt_apply(obj->transmat, \
			cyl->valid_poi, FWDFM);
		cyl->global_origin = gt_apply(obj->transmat, \
			cyl->local_origin, FWDFM);
		set_vect(cyl->org_normal, cyl->valid_poi->data[0][0], \
			cyl->valid_poi->data[1][0], 0.0);
		scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, \
			cyl->org_normal, FWDFM), cyl->global_origin);
		nml_mat_normalize_r(scn->v_lc_norm);
		scn->v_lc_color = nml_mat_cp(obj->v_base_color);
		return (1);
	}
	else
		cyl_not_side_inter(obj, scn, cyl);
	return (0);
}
