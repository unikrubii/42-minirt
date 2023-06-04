/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:44:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/04 17:10:37 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTBASE_H
# define OBJECTBASE_H

# include "nml_matrix.h"
# include "ray.h"
# include "minirt.h"
# include "scene.h"
# include "gtform.h"

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
	t_gtform			*transmat;
	struct s_objbase	*next;

	void				(*obj_init)(struct s_objbase *);
	void				(*obj_deinit)(struct s_objbase *);
	int					(*obj_test_intersect)(t_ray *ray, \
		t_nml_mat *int_point, t_nml_mat *lc_normal, t_nml_mat *lc_color);
	int					(*obj_test_inter_scn)(struct s_objbase *, t_scene *scn);
	int					(*obj_close_enough)(float f1, float f2);
	void				(*obj_set_trans_mat)(t_gtform *form, t_gtform *transmat);
}	t_objbase;

typedef struct s_inter_calc
{
	t_nml_mat	*vhat;
	t_nml_mat	*vtmp;
	float		b;
	float		c;
	float		inter_test;
	float		num_sqrt;
	float		t1;
	float		t2;
	t_ray		*bck_ray;
	t_nml_mat	*v_poi;
	t_nml_mat	*v_obj_org;
	t_nml_mat	*v_obj_norg;
	t_nml_mat	*k;
	float		t;
	float		u;
	float		v;
	t_nml_mat	*v_obj_norm;
	t_nml_mat	*v_obj_gorg;
}	t_inter_calc;

void	obj_init(t_objbase *obj, int type, t_fattr *attr);
void	obj_deinit(t_objbase *obj);
int		obj_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color);
int		obj_close_enough(float f1, float f2);
void	obj_set_trans_mat(t_gtform *form, t_gtform *transmat);

void	sphere_init(t_objbase *obj);
void	sphere_deinit(t_objbase *obj);
int		sphere_test_intersect(t_ray *ray, t_nml_mat *int_point, \
	t_nml_mat *lc_normal, t_nml_mat *lc_color);
int		sphere_test_inter_scn(t_objbase *obj, t_scene *scn);
void	plane_init(t_objbase *obj);
void	plane_deinit(t_objbase *obj);
int		plane_test_inter_scn(t_objbase *obj, t_scene *scn);

t_objbase	*objlst_last(t_objbase *lst);
void		objlst_add_back(t_objbase **lst, t_objbase *new);
t_objbase	*objlst_new(int type, t_fattr *attr);
void		objlst_clear(t_objbase **lst);
void		objlst_print(t_objbase *lst);

#endif
