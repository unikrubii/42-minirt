/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:53:59 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/04 17:10:59 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTFORM_H
# define GTFORM_H

# include "nml_matrix.h"
# include "camera.h"
# include "ray.h"

# define FWDFM 1
# define BWDFM 0

typedef struct s_fattr
{
	t_nml_mat	*v_tr;
	t_nml_mat	*v_rot;
	t_nml_mat	*v_scl;
	t_nml_mat	*v_color;
	t_nml_mat	*up_v;
}	t_fattr;

typedef struct s_gtform
{
	t_nml_mat		*fwd;
	t_nml_mat		*bwd;
	t_nml_mat		*fwdtfm;
	t_nml_mat		*bwdtfm;

	void			(*gt_form_init)(struct s_gtform *gt_form, \
		t_nml_mat *fwd, t_nml_mat *bwd);
	void			(*gt_form_deinit)(struct s_gtform *gt_form);
	void			(*gt_set_trans)(t_nml_mat *trans, t_nml_mat *rot, \
		t_nml_mat *scale);

	t_nml_mat		*(*gt_get_fwd)(struct s_gtform *gt_form);
	t_nml_mat		*(*gt_get_bwd)(struct s_gtform *gt_form);
	t_ray			*(*ray_apply)(struct s_gtform *gt_form, t_ray *ray, \
		int dir);
	t_nml_mat		*(*gt_apply)(struct s_gtform *gt_form, t_nml_mat *v_inp, \
		int dir);

}	t_gtform;

void		gt_init(t_gtform *form);
void		gt_deinit(t_gtform *form);

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

#endif
