/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:08:24 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/18 14:20:35 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# define _GNU_SOURCE

# include "nml_matrix.h"
# include "v_util.h"

typedef struct s_camera
{
	t_nml_mat	*v_cam_pos;
	t_nml_mat	*v_cam_lookat;
	t_nml_mat	*v_cam_up;
	float		cam_len;
	float		cam_hor_size;
	float		cam_aspr;
	t_nml_mat	*v_align_vect;
	t_nml_mat	*v_proj_scr_u;
	t_nml_mat	*v_proj_scr_v;
	t_nml_mat	*v_proj_scr_cen;

	t_nml_mat	(* getfn_mat)(struct s_camera *);
	float		(* getfn_flt)(struct s_camera *);
	void		(* setfn_uvw)(struct s_camera *, float, float, float);
	void		(* setval)(struct s_camera *, float);
}	t_camera;

void	camera_init(t_camera *camera);

#endif
