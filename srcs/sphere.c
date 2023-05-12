/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/13 02:19:37 by nnakarac         ###   ########.fr       */
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

int		sphere_test_intersect(t_ray *castray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color)
{
	t_nml_mat	*vhat;
	t_nml_mat	*vtmp;
	float		b;
	float		c;
	float		inter_test;
	float		num_sqrt;
	float		t1;
	float		t2;

	(void) int_point;
	(void) lc_normal;
	(void) lc_color;
	// compute values of a b and c
	vhat = nml_mat_cp(castray->v_lab);
	nml_vect_normalize_r(vhat);

	/* Note that a is equal to the squared magitude of the
	direction of the cast ray. As this will be a unit vector,
	we can conclude that the value of 'a' will always be 1. */
	// a = 1.0;

	// Calculate b.
	b = 2.0 * nml_vect_dot(castray->v_point1, 0, vhat, 0);

	// Calculate c.
	c = nml_vect_dot(castray->v_point1, 0, castray->v_point1, 0) - 1.0;

	//Test whether we actually have and intesection
	inter_test = (b * b) - 4.0 * c;

	if (inter_test > 0.0)
	{
		num_sqrt = sqrt(inter_test);
		t1 = (-b + num_sqrt) / 2.0;
		t2 = (-b - num_sqrt) / 2.0;

		// printf("inter_test|%f\n", inter_test);
		// printf("num_sqrt|%f\n", num_sqrt);
		// printf("T|%f:%f\n", t1, t2);
		if ((t1 < 0.0) || (t2 < 0.0))
		{
			nml_mat_free(vhat);
			return (0);
		}
		else
		{
			if (t1 < t2)
			{
				vtmp = nml_mat_smult(vhat, t1);
				nml_mat_add_r(vtmp, castray->v_point1);
				set_vect(int_point, vtmp->data[0][0], vtmp->data[1][0], vtmp->data[2][0]);
				nml_mat_free(vtmp);
			}
			else
			{
				vtmp = nml_mat_smult(vhat, t2);
				nml_mat_add_r(vtmp, castray->v_point1);
				set_vect(int_point, vtmp->data[0][0], vtmp->data[1][0], vtmp->data[2][0]);
				nml_mat_free(vtmp);
			}
		}
		nml_mat_free(vhat);
		return (1);
	}
	else
	{
		nml_mat_free(vhat);
		return (0);
	}
}
