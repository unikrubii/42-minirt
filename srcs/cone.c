/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/21 00:11:01 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	cone_init(t_objbase *obj)
{
	(void) obj;
}

void	cone_deinit(t_objbase *obj)
{
	(void) obj;
}

void	cone_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	// Copy the ray and apply the bwd
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->a = powf(calc->vhat->data[0][0], 2.0) + powf(calc->vhat->data[1][0], 2.0) - \
		powf(calc->vhat->data[2][0], 2.0);
	calc->b = 2.0 * ((calc->bck_ray->v_point1->data[0][0] * calc->vhat->data[0][0]) + \
		(calc->bck_ray->v_point1->data[1][0] * calc->vhat->data[1][0]) - \
		(calc->bck_ray->v_point1->data[2][0] * calc->vhat->data[2][0]));
	calc->c = powf(calc->bck_ray->v_point1->data[0][0], 2.0) + \
		powf(calc->bck_ray->v_point1->data[1][0], 2.0) - \
		powf(calc->bck_ray->v_point1->data[2][0], 2.0);
	calc->inter_test = sqrtf(powf(calc->b, 2.0) - (4.0 * calc->a * calc->c));
}

int	cone_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	cone;
	t_nml_mat		*poi[3];
	float			t[3];
	int				t1_valid;
	int				t2_valid;
	int				t3_valid;

	cone_compute_values(&cone, scn, obj);
	t1_valid = 0;
	t2_valid = 0;
	t3_valid = 0;
	poi[0] = new_vector();
	poi[1] = new_vector();
	poi[2] = new_vector();
	cone.v_poi = new_vector();
	if (cone.inter_test > 0.0)
	{
		// compute teh values of t
		t[0] = (-cone.b + cone.inter_test) / (2 * cone.a);
		t[1] = (-cone.b - cone.inter_test) / (2 * cone.a);

		// compute the points of intersection
		poi[0] = nml_mat_add(cone.bck_ray->v_point1, nml_mat_smult(cone.vhat, t[0]));
		poi[1] = nml_mat_add(cone.bck_ray->v_point1, nml_mat_smult(cone.vhat, t[1]));

		if ((t[0] > 0.0) && (poi[0]->data[2][0] > 0.0) && (poi[0]->data[2][0] < 1.0))
		{
			t1_valid = 1;
		}
		else
		{
			t1_valid = 0;
			t[0] = 100e6;
		}
		if ((t[1] > 0.0) && (poi[1]->data[2][0] > 0.0) && (poi[1]->data[2][0] < 1.0))
		{
			t2_valid = 1;
		}
		else
		{
			t2_valid = 0;
			t[1] = 100e6;
		}
	}
	else
	{
		t1_valid = 0;
		t2_valid = 0;
		t[0] = 100e6;
		t[1] = 100e6;
	}
	// And test the end cap
	if (obj_close_enough(cone.vhat->data[2][0], 0.0))
	{
		t3_valid = 0;
		t[2] = 100e6;
	}
	else
	{
		// compute the values of t
		t[2] = (cone.bck_ray->v_point1->data[2][0] - 1.0) / -cone.vhat->data[2][0];

		// compute the points of intersection
		poi[2] = nml_mat_add(cone.bck_ray->v_point1, nml_mat_smult(cone.vhat, t[2]));

		// check if any of these are valid
		if ((t[2] > 0.0) && (sqrtf(powf(poi[2]->data[0][0], 2.0) + \
			powf(poi[2]->data[1][0], 2.0)) < 1.0))
			t3_valid = 1;
		else
		{
			t3_valid = 0;
			t[2] = 100e6;
		}
	}
	// if no valid intersection
	if (!t1_valid && !t2_valid && !t3_valid)
		return 0;
	
	// Check for the smalloes valid value of t
	int		min_i;
	float	min_t;
	int		i;

	min_i = 0;
	min_t = 10e6;
	i = 0;
	while (i < 3)
	{
		if (t[i] < min_t)
		{
			min_t = t[i];
			min_i = i;
		}
		i++;
	}
	// if minIndex is 0 or 1, we have a side intersection
	t_nml_mat	*valid_poi;
	t_nml_mat	*org_normal;
	t_nml_mat	*local_origin;
	t_nml_mat	*global_origin;
	float		tx;
	float		ty;
	float		tz;

	valid_poi = nml_mat_cp(poi[min_i]);
	local_origin = new_vector();
	set_vect(local_origin, 0.0, 0.0, 0.0);
	global_origin = new_vector();
	org_normal = new_vector();
	// transform the intersection point to world coordinates
	scn->v_intpoint = gt_apply(obj->transmat, valid_poi, FWDFM);
	global_origin = gt_apply(obj->transmat, local_origin, FWDFM);
	if (min_i < 2)
	{
		tx = valid_poi->data[0][0];
		ty = valid_poi->data[1][0];
		tz = -sqrtf(powf(tx, 2.0) + powf(ty, 2.0));
		set_vect(org_normal, tx, ty, tz);
		scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, org_normal, FWDFM), \
			global_origin);
		nml_mat_normalize_r(scn->v_lc_norm);
		// Return the base color
		scn->v_lc_color = nml_mat_cp(obj->v_base_color);
		return 1;
	}
	else
	{
		if (!obj_close_enough(cone.vhat->data[2][0], 0.0))
		{
			if (sqrtf(powf(valid_poi->data[0][0], 2.0) + powf(valid_poi->data[1][0], 2.0)) < 1.0)
			{
				// compute the local normal
				set_vect(org_normal, 0.0, 0.0, 1.0);
				scn->v_lc_norm = nml_mat_sub(gt_apply(obj->transmat, org_normal, FWDFM), \
					global_origin);
				nml_mat_normalize_r(scn->v_lc_norm);
				// return the base color
				scn->v_lc_color = nml_mat_cp(obj->v_base_color);
				return 1;
			}
			else
				return 0;
		}
		else
			return 0;
	}
	return 0;
}
