/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:26:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/29 19:43:36 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	float		b;
	float		c;
	float		inter_test;

	(void) int_point;
	(void) lc_normal;
	(void) lc_color;
	// compute values of a b and c
	vhat = nml_mat_cp(castray->v_lab);
	nml_mat_normalize_r(vhat);

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
		return (1);
	else
		return (0);
}
