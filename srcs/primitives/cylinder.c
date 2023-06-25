/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 05:00:13 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	cylinder_compute_values(t_inter_calc *calc, t_scene *scn, \
	t_objbase *obj)
{
	calc->bck_ray = ray_apply(obj->transmat, scn->cam_ray, BWDFM);
	calc->vhat = nml_mat_cp(calc->bck_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->a = powf(calc->vhat->data[0][0], 2) + \
		powf(calc->vhat->data[1][0], 2);
	calc->b = 2.0 * (calc->bck_ray->v_point1->data[0][0] * \
		calc->vhat->data[0][0] + calc->bck_ray->v_point1->data[1][0] * \
		calc->vhat->data[1][0]);
	calc->c = powf(calc->bck_ray->v_point1->data[0][0], 2) + \
		powf(calc->bck_ray->v_point1->data[1][0], 2) - 1.0;
	calc->inter_test = sqrtf(powf(calc->b, 2) - 4.0 * calc->a * calc->c);
}

void	cyl_init_att(t_inter_calc *cyl)
{
	cyl->t1_valid = 0;
	cyl->t2_valid = 0;
	cyl->t3_valid = 0;
	cyl->t4_valid = 0;
	cyl->v_poi = new_vector();
	cyl->v_obj_org = new_vector();
	cyl->poi[0] = new_vector();
	cyl->poi[1] = new_vector();
	cyl->poi[2] = new_vector();
	cyl->poi[3] = new_vector();
	cyl->tt[0] = 0.0;
	cyl->tt[1] = 0.0;
	cyl->tt[2] = 0.0;
	cyl->tt[3] = 0.0;
	set_vect(cyl->v_obj_org, 0.0, 0.0, 0.0);
}

void	cyl_inter_test(t_inter_calc *cyl)
{
	cyl->tt[0] = (-cyl->b + cyl->inter_test) / (2 * cyl->a);
	cyl->tt[1] = (-cyl->b - cyl->inter_test) / (2 * cyl->a);
	cyl->poi[0] = nml_mat_add(cyl->bck_ray->v_point1, \
		nml_mat_smult(cyl->vhat, cyl->tt[0]));
	cyl->poi[1] = nml_mat_add(cyl->bck_ray->v_point1, \
		nml_mat_smult(cyl->vhat, cyl->tt[1]));
	if ((cyl->tt[0] > 0.0) && (fabs(cyl->poi[0]->data[2][0]) < 1.0))
		cyl->t1_valid = 1;
	else
	{
		cyl->t1_valid = 0;
		cyl->tt[0] = 100e6;
	}
	if ((cyl->tt[1] > 0.0) && (fabs(cyl->poi[1]->data[2][0]) < 1.0))
		cyl->t2_valid = 1;
	else
	{
		cyl->t2_valid = 0;
		cyl->tt[1] = 100e6;
	}
}

int	cylinder_test_inter_scn(t_objbase *obj, t_scene *scn)
{
	t_inter_calc	cyl;

	cylinder_compute_values(&cyl, scn, obj);
	cyl_init_att(&cyl);
	if (cyl.inter_test > 0.0)
		cyl_inter_test(&cyl);
	else
	{
		cyl.t1_valid = 0;
		cyl.t2_valid = 0;
		cyl.tt[0] = 100e6;
		cyl.tt[1] = 100e6;
	}
	cyl_close_enough(&cyl);
	if (!cyl.t1_valid && !cyl.t2_valid && !cyl.t3_valid && !cyl.t4_valid)
		return (0);
	cyl_get_min(&cyl);
	return (cyl_side_inter(obj, scn, &cyl));
}
