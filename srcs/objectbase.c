/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:19:45 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/29 11:52:45 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

void	obj_init(t_objbase *obj)
{

}

void	obj_deinit(t_objbase *obj)
{

}

int		obj_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color)
{
	return (0);
}

int		obj_close_enough(float f1, float f2)
{
	return (fabs(f1 - f2) < EPSILON);
}
