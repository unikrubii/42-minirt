/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:19:45 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 21:47:58 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

void	obj_init_util(t_objbase *obj, int type, t_fattr *attr, int id)
{
	(void) id;
	if (attr->mat)
	{
		obj->material = attr->mat;
		obj->has_material = 1;
	}
	if (type == SPH)
	{
		obj->obj_init = sphere_init;
		obj->obj_test_inter_scn = sphere_test_inter_scn;
		obj->obj_init(obj);
		obj->obj_deinit = sphere_deinit;
	}
	if (type == PLN)
	{
		obj->obj_init = plane_init;
		obj->obj_test_inter_scn = plane_test_inter_scn;
		obj->obj_init(obj);
		obj->obj_deinit = plane_deinit;
	}
	if (type == CYL)
	{
		obj->obj_init = cylinder_init;
		obj->obj_test_inter_scn = cylinder_test_inter_scn;
		obj->obj_init(obj);
		obj->obj_deinit = cylinder_deinit;
	}
}

void	obj_init(t_objbase *obj, int type, t_fattr *attr, int id)
{
	obj->type = type;
	obj->id = id;
	obj->v_base_color = nml_mat_cp(attr->v_color);
	obj->obj_close_enough = obj_close_enough;
	obj->transmat = malloc(sizeof(t_gtform) * 1);
	gt_set_trans(obj->transmat, attr->v_tr, attr->v_rot, attr->v_scl);
	obj->next = NULL;
	obj->has_material = 0;
	obj->material = NULL;
	obj_init_util(obj, type, attr, id);
}

void	obj_deinit(t_objbase *obj)
{
	(void) obj;
	if (obj->v_base_color)
	{
		nml_mat_free(obj->v_base_color);
		obj->v_base_color = NULL;
	}
	if (obj->transmat)
	{
		if (obj->type != PLN)
			gt_deinit_mode(obj->transmat, 1);
		else
			gt_deinit_mode(obj->transmat, 0);
		obj->transmat = NULL;
	}
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
