/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:44:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 22:20:41 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTBASE_H
# define OBJECTBASE_H

# include "nml_matrix.h"
# include "ray.h"

/// @brief ENUM Object type
/// @note 1, SPH - Sphere
/// @note 2, PLN - Plane
/// @note 3, CYL - Cylinder
/// @note 4, CON - Cone
/// @note 5, HYB - Hyperboloid
/// @note 6, PLB - Paraboloid
enum e_objtype {
	SPH = 1,
	PLN = 2,
	CYL = 3,
	CON = 4,
	HYB = 5,
	PLB = 6
};

typedef struct s_objbase
{
	int					type;
	t_nml_mat			*v_base_color;
	struct s_objbase	*next;

	void				(*obj_init)(struct s_objbase *);
	void				(*obj_deinit)(struct s_objbase *);
	int					(*obj_test_intersect)(t_ray *ray, \
		t_nml_mat *int_point, t_nml_mat *lc_normal, t_nml_mat *lc_color);
	int					(*obj_close_enough)(float f1, float f2);
}	t_objbase;

void	obj_init(t_objbase *obj, int type);
void	obj_deinit(t_objbase *obj);
int		obj_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color);
int		obj_close_enough(float f1, float f2);

void	sphere_init(t_objbase *obj);
void	sphere_deinit(t_objbase *obj);
int		sphere_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color);

#endif
