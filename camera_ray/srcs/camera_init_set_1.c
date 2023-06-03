/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init_set_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:28:14 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 13:00:06 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"

/// @brief Camera initialization
/// @param camera
void	camera_init(t_camera *camera)
{
	camera->v_cam_pos = new_vector();
	camera->v_cam_lookat = new_vector();
	camera->v_cam_up = new_vector();
	camera->v_align_vect = NULL;
	camera->v_proj_scr_u = NULL;
	camera->v_proj_scr_v = NULL;
	camera->v_proj_scr_cen = NULL;
	set_vect(camera->v_cam_pos, 0.0, 0.0, 0.0);
	set_vect(camera->v_cam_lookat, 0.0, 0.0, 0.0);
	set_vect(camera->v_cam_up, 0.0, 0.0, 0.0);
	camera->cam_len = 1.0;
	camera->cam_hor_size = 1.0;
	camera->cam_aspr = 1.0;
}

/// @brief Camera deinitialization
/// @param camera
void	camera_deinit(t_camera *camera)
{
	nml_mat_free(camera->v_cam_pos);
	nml_mat_free(camera->v_cam_lookat);
	nml_mat_free(camera->v_cam_up);
	nml_mat_free(camera->v_align_vect);
	nml_mat_free(camera->v_proj_scr_cen);
	nml_mat_free(camera->v_proj_scr_u);
	nml_mat_free(camera->v_proj_scr_v);
}

/// @brief Set camera position in vector format
/// @param camera
/// @param u
/// @param v
/// @param w
void	cam_set_pos(t_camera *camera, float u, float v, float w)
{
	set_vect(camera->v_cam_pos, u, v, w);
}

/// @brief Set camera position in vector format
/// @param camera
/// @param u
/// @param v
/// @param w
void	cam_set_lookat(t_camera *camera, float u, float v, float w)
{
	set_vect(camera->v_cam_lookat, u, v, w);
}

/// @brief Set camera up vector
/// @param camera
/// @param u
/// @param v
/// @param w
void	cam_set_up(t_camera *camera, float u, float v, float w)
{
	set_vect(camera->v_cam_up, u, v, w);
}
