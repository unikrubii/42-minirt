/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbaseutil.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 23:03:14 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 23:05:38 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

int	obj_close_enough(float f1, float f2)
{
	return (fabs(f1 - f2) < EPSILON);
}

void	obj_set_trans_mat(t_gtform *form, t_gtform *transmat)
{
	gt_form_assign(form, transmat);
}

// Function to assign a material
int	obj_assign_material(t_objbase *obj, t_matbase *material)
{
	obj->material = material;
	obj->has_material = 1;
	return (obj->has_material);
}
