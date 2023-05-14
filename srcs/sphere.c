/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/15 00:14:12 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "objectbase.h"

void	sphere_init(t_objbase *obj)
{
	(void) obj;
}

void	sphere_deinit(t_objbase *obj)
{
	(void) obj;
}

void	compute_values(t_inter_calc *calc, t_scene *scn)
{
	calc->vhat = nml_mat_cp(scn->cam_ray->v_lab);
	nml_vect_normalize_r(calc->vhat);
	calc->b = 2.0 * nml_vect_dot(scn->cam_ray->v_point1, 0, calc->vhat, 0);
	calc->c = nml_vect_dot(scn->cam_ray->v_point1, 0, \
		scn->cam_ray->v_point1, 0) - 1.0;
	calc->inter_test = (calc->b * calc->b) - 4.0 * calc->c;
}

void	inter_calc(t_inter_calc *calc, t_scene *scn)
{
	if (calc->t1 < calc->t2)
	{
		calc->vtmp = nml_mat_smult(calc->vhat, calc->t1);
		nml_mat_add_r(calc->vtmp, scn->cam_ray->v_point1);
		set_vect(scn->v_intpoint, calc->vtmp->data[0][0], \
			calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
		nml_mat_free(calc->vtmp);
	}
	else
	{
		calc->vtmp = nml_mat_smult(calc->vhat, calc->t2);
		nml_mat_add_r(calc->vtmp, scn->cam_ray->v_point1);
		set_vect(scn->v_intpoint, calc->vtmp->data[0][0], \
			calc->vtmp->data[1][0], calc->vtmp->data[2][0]);
		nml_mat_free(calc->vtmp);
	}
	set_vect(scn->v_lc_norm, scn->v_intpoint->data[0][0], \
		scn->v_intpoint->data[1][0], scn->v_intpoint->data[2][0]);
	nml_vect_normalize_r(scn->v_lc_norm);
}

int	sphere_test_inter_scn(t_scene *scn)
{
	t_inter_calc	sph;

	compute_values(&sph, scn);
	if (sph.inter_test > 0.0)
	{
		sph.num_sqrt = sqrt(sph.inter_test);
		sph.t1 = (-sph.b + sph.num_sqrt) / 2.0;
		sph.t2 = (-sph.b - sph.num_sqrt) / 2.0;
		if ((sph.t1 < 0.0) || (sph.t2 < 0.0))
			return (nml_mat_free(sph.vhat), 0);
		else
			inter_calc(&sph, scn);
		return (nml_mat_free(sph.vhat), 1);
	}
	else
		return (nml_mat_free(sph.vhat), 0);
}
