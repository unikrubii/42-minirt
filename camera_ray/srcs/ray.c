/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:05:33 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 21:08:57 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

/// @brief Ray initialization
/// @param ray
/// @param v_point1 camera position i.e. camera->v_proj_scr_v
/// @param v_point2 screen world coordinate i.e. pro_scr_y
void	ray_init(t_ray *ray, t_nml_mat *v_point1, t_nml_mat *v_point2)
{
	ray->v_point1 = nml_mat_cp(v_point1);
	ray->v_point2 = nml_mat_cp(v_point2);
	ray->v_lab = nml_mat_cp(v_point1);
	nml_mat_sub_r(ray->v_lab, ray->v_point2);
}

t_nml_mat	*ray_get_point(t_ray *ray, int point)
{
	if (point == 1)
		return (ray->v_point1);
	else if (point == 2)
		return (ray->v_point2);
	else
		return (NULL);
}
