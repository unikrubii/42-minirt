/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:19:45 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/20 21:46:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

void	obj_init(t_objbase *obj, int type, t_fattr *attr)
{
	obj->type = type;
	obj->v_base_color = nml_mat_cp(attr->v_color);
	obj->obj_close_enough = obj_close_enough;
	obj->transmat = malloc(sizeof(t_gtform) * 1);
	gt_set_trans(obj->transmat, attr->v_tr, attr->v_rot, attr->v_scl);
	obj->next = NULL;
	if (type == SPH)
	{
		obj->obj_init = sphere_init;
		obj->obj_test_inter_scn = sphere_test_inter_scn;
		obj->obj_init(obj);
	}
}

void	obj_deinit(t_objbase *obj)
{
	(void) obj;
}

int	obj_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color)
{
	(void) ray;
	(void) int_point;
	(void) lc_normal;
	(void) lc_color;
	return (0);
}

int	obj_close_enough(float f1, float f2)
{
	return (fabs(f1 - f2) < EPSILON);
}

void	obj_set_trans_mat(t_gtform *form, t_gtform *transmat)
{
	gt_form_assign(form, transmat);
}
