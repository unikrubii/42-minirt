/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:44:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/29 10:26:05 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTBASE_H
# define OBJECTBASE_H

# include "nml_matrix.h"
# include "v_util.h"
# include "ray.h"

typedef struct s_objbase
{
	t_nml_mat	*v_base_color;
	int			(*obj_test_intersect)(t_ray *, t_nml_mat *, \
		t_nml_mat *, t_nml_mat *);
	int			(*obj_close_enough)(float, float);
}	t_objbase;

void	obj_init(t_objbase *obj);

void	obj_deinit(t_objbase *obj);

int		obj_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color);

int		obj_close_enough(float f1, float f2);

#endif
