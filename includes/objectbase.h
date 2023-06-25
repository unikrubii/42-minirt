/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectbase.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 09:44:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 21:47:37 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTBASE_H
# define OBJECTBASE_H

# include "nml_matrix.h"
# include "ray.h"
# include "scene.h"
# include "t_base.h"
# include "gtform.h"

void	obj_init(t_objbase *obj, int type, t_fattr *attr, int id);
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
void	cylinder_init(t_objbase *obj);
void	cylinder_deinit(t_objbase *obj);
int		cylinder_test_inter_scn(t_objbase *obj, t_scene *scn);


t_objbase	*objlst_last(t_objbase *lst);
void		objlst_add_back(t_objbase **lst, t_objbase *new);
t_objbase	*objlst_new(int type, t_fattr *attr, int id);
void		objlst_clear(t_objbase **lst);
void		objlst_print(t_objbase *lst);

int			obj_assign_material(t_objbase *obj, t_matbase *material);

void		mat_init(t_matbase *mat);
void		mat_deinit(t_matbase *mat);

void		compute_color(t_handle *handy, t_objbase *closet_obj, t_scene *scn);
void		compute_specular(t_handle *handy, t_objbase *closet_obj, t_scene *scn);
void		compute_diffuse_color(t_handle *handy, t_objbase *closet_obj, t_scene *scn);
void		compute_reflect_color(t_handle *handy, t_objbase *obj, t_scene *scn, t_scene *rfl_scn);

void		simple_compute_color(t_handle *handy, t_objbase *obj, t_scene *scn);
void		simple_compute_specular(t_handle *handy, t_objbase *obj, t_scene *scn);

int			cast_ray(t_scene *scn, t_handle *handy, t_objbase *this_obj, t_objbase **closet_obj);


#endif
