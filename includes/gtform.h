/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:53:59 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 21:40:43 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTFORM_H
# define GTFORM_H

# include "nml_matrix.h"
# include "camera.h"
# include "ray.h"
# include "t_base.h"

# define FWDFM 1
# define BWDFM 0

int			mateqdim_num(t_nml_mat *mat, unsigned int size);

void		gt_init(t_gtform *form);
void		gt_deinit(t_gtform *form);
void		gt_deinit_mode(t_gtform *form, int mode);

void		gt_form_init(t_gtform *form, t_nml_mat *fwd, t_nml_mat *bwd);
void		gt_form_deinit(t_gtform *form);
void		gt_set_trans(t_gtform *form, t_nml_mat *trans, t_nml_mat *rot, \
	t_nml_mat *scale);

t_nml_mat	*gt_get_fwd(t_gtform *form);
t_nml_mat	*gt_get_bwd(t_gtform *form);

t_ray		*ray_apply(t_gtform *form, t_ray *ray, int dir);
t_nml_mat	*gt_apply(t_gtform *form, t_nml_mat *v_inp, int dir);

t_gtform	*gt_form_mult(t_gtform *lhs, t_gtform *rhs);
void		gt_form_assign(t_gtform *lhs, t_gtform *rhs);

void		set_trans_mat(t_nml_mat *mat, t_nml_mat *trans);
void		set_rotz_mat(t_nml_mat *mat, t_nml_mat *rot);
void		set_roty_mat(t_nml_mat *mat, t_nml_mat *rot);
void		set_rotx_mat(t_nml_mat *mat, t_nml_mat *rot);
void		set_scale_mat(t_nml_mat *mat, t_nml_mat *scale);


#endif
