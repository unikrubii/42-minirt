/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:16:09 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/18 19:57:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "v_util.h"

/// @brief Function to compute camera geometry
/// @note 1. Compute a vector from the camera position to the LookAt position.
/// @note 2. Compute the U and V vectors.
/// @param camera
void	update_cam_geomet(t_camera *camera)
{
	camera->v_align_vect = nml_mat_sub(camera->v_cam_lookat, \
		camera->v_cam_pos);
	nml_mat_normalize_r(camera->v_align_vect);
	camera->v_proj_scr_u =
}
