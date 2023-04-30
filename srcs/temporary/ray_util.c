/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 14:24:23 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/23 15:34:39 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

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
