/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:53:59 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/19 09:50:16 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTFORM_H
# define GTFORM_H

# include "nml_matrix.h"
# include "camera.h"
# include "ray.h"

# define FWDFM 1
# define BWDFM 0

typedef struct s_gtform
{
	t_nml_mat		*fwd;
	t_nml_mat		*bwd;
	t_nml_mat		*fwdtfm;
	t_nml_mat		*bwdtfm;

	struct s_gtform	(*gt_form_init)(struct s_gtform *gt_form, \
		t_nml_mat *fwd, t_nml_mat *bwd);
	void			(*gt_form_deinit)(struct s_gtform *gt_form);
	void			(*gt_set_trans)(t_nml_mat *trans, t_nml_mat *rot, \
		t_nml_mat *scale);

	t_nml_mat		(*gt_get_fwd)(struct s_gtform *gt_form);
	t_nml_mat		(*gt_get_bwd)(struct s_gtform *gt_form);
	t_ray			(*ray_apply)(struct s_gtform *gt_form, t_ray *ray, \
		int dir);
	t_nml_mat		(*gt_apply)(struct s_gtform *gt_form, t_nml_mat *v_inp, \
		int dir);


}	t_gtform;

#endif
