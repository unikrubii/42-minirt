/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:19:45 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/06 00:19:51 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

void	obj_init(t_objbase *obj, int type)
{
	obj->type = type;
	obj->v_base_color = new_vector();
	obj->obj_close_enough = obj_close_enough;
	obj->next = NULL;
	if (type == SPH)
	{
		obj->obj_init = sphere_init;
		obj->obj_test_intersect = sphere_test_intersect;
	}
}

void	obj_deinit(t_objbase *obj)
{
	(void) obj;
}

int		obj_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color)
{
	(void) ray;
	(void) int_point;
	(void) lc_normal;
	(void) lc_color;
	return (0);
}

int		obj_close_enough(float f1, float f2)
{
	return (fabs(f1 - f2) < EPSILON);
}
