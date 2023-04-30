/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:22:30 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 21:21:25 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# define _GNU_SOURCE

# include "nml_matrix.h"
# include "ray.h"

typedef struct	s_ray
{
	t_nml_mat	*v_point1;
	t_nml_mat	*v_point2;
	t_nml_mat	*v_lab;
}	t_ray;

void		ray_init(t_ray *ray, t_nml_mat *v_point1, t_nml_mat *v_point2);

t_nml_mat	*ray_get_point(t_ray *ray, int point);

#endif
