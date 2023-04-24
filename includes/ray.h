/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 10:02:01 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/23 14:55:31 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "nml_matrix.h"
# include "v_util.h"

typedef struct	s_ray
{
	t_nml_mat	*v_point1;
	t_nml_mat	*v_point2;
	t_nml_mat	*v_lab;
}	t_ray;

void		ray_init(t_ray *ray, t_nml_mat *v_point1, t_nml_mat *v_point2);

t_nml_mat	*ray_get_point(t_ray *ray, int point);

#endif
