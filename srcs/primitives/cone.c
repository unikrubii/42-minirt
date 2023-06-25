/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 04:29:01 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	cone_compute_values(t_inter_calc *calc, t_scene *scn, t_objbase *obj)
{
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->a = powf(calc->vhat->data[0][0], 2.0) + \
		powf(calc->vhat->data[1][0], 2.0) - powf(calc->vhat->data[2][0], 2.0);
	calc->b = 2.0 * ((calc->bck_ray->v_point1->data[0][0] * \
		calc->vhat->data[0][0]) + (calc->bck_ray->v_point1->data[1][0] * \
		calc->vhat->data[1][0]) - (calc->bck_ray->v_point1->data[2][0] * \
		calc->vhat->data[2][0]));
	calc->c = powf(calc->bck_ray->v_point1->data[0][0], 2.0) + \
		powf(calc->bck_ray->v_point1->data[1][0], 2.0) - \
		powf(calc->bck_ray->v_point1->data[2][0], 2.0);
	calc->inter_test = sqrtf(powf(calc->b, 2.0) - (4.0 * calc->a * calc->c));
}

void	cone_init_att(t_inter_calc *cone)
{
	cone->t1_valid = 0;
	cone->t2_valid = 0;
	cone->t3_valid = 0;
	cone->poi[0] = new_vector();
	cone->poi[1] = new_vector();
	cone->poi[2] = new_vector();
	cone->v_poi = new_vector();
	cone->tt[0] = 0.0;
	cone->tt[1] = 0.0;
	cone->tt[2] = 0.0;
}

void	cone_inter_test(t_inter_calc *cone)
{
	cone->tt[0] = (-cone->b + cone->inter_test) / (2 * cone->a);
	cone->tt[1] = (-cone->b - cone->inter_test) / (2 * cone->a);
	cone->poi[0] = nml_mat_add(cone->bck_ray->v_point1, \
		nml_mat_smult(cone->vhat, cone->tt[0]));
	cone->poi[1] = nml_mat_add(cone->bck_ray->v_point1, \
		nml_mat_smult(cone->vhat, cone->tt[1]));
	if ((cone->tt[0] > 0.0) && (cone->poi[0]->data[2][0] > 0.0) && \
		(cone->poi[0]->data[2][0] < 1.0))
		cone->t1_valid = 1;
	else
	{
		cone->t1_valid = 0;
		cone->tt[0] = 100e6;
	}
	if ((cone->tt[1] > 0.0) && (cone->poi[1]->data[2][0] > 0.0) && \
		(cone->poi[1]->data[2][0] < 1.0))
		cone->t2_valid = 1;
	else
	{
		cone->t2_valid = 0;
		cone->tt[1] = 100e6;
	}
}

int	cone_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	cone;

	cone_compute_values(&cone, scn, obj);
	cone_init_att(&cone);
	if (cone.inter_test > 0.0)
		cone_inter_test(&cone);
	else
	{
		cone.t1_valid = 0;
		cone.t2_valid = 0;
		cone.tt[0] = 100e6;
		cone.tt[1] = 100e6;
	}
	cone_close_enough(&cone);
	if (!cone.t1_valid && !cone.t2_valid && !cone.t3_valid)
		return (0);
	cone_get_min(&cone);
	return (cone_side_inter(obj, scn, &cone));
}
