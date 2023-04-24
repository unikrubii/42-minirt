/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 07:08:24 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/23 17:11:39 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# define _GNU_SOURCE

# include "nml_matrix.h"
# include "v_util.h"
# include "ray.h"

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

void		camera_init(t_camera *camera);

void		cam_set_pos(t_camera *camera, float u, float v, float w);

void		cam_set_lookat(t_camera *camera, float u, float v, float w);

void		cam_set_up(t_camera *camera, float u, float v, float w);

void		cam_set_length(t_camera *camera, float len);

void		cam_set_hor_size(t_camera *camera, float size);

void		cam_set_aspr(t_camera *camera, float ratio);

t_nml_mat	cam_get_pos(t_camera *camera);

t_nml_mat	cam_get_lookat(t_camera *camera);

t_nml_mat	cam_get_up(t_camera *camera);

float		cam_get_length(t_camera *camera);

float		cam_get_hor_size(t_camera *camera);

float		cam_get_aspr(t_camera *camera);

t_nml_mat	cam_get_scr_u(t_camera *camera);

t_nml_mat	cam_get_scr_v(t_camera *camera);

t_nml_mat	cam_get_scr_cen(t_camera *camera);

void		update_cam_geomet(t_camera *camera);

t_ray		*generate_ray(t_camera *camera, float pro_scr_x, float pro_scr_y);

#endif
