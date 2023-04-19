/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_6.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:16:09 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/19 22:46:56 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "v_util.h"

/// @brief Function to compute camera geometry
/// @note 1. Compute a vector from the camera position to the LookAt position.
/// @note 2. Compute the U and V vectors.
/// @note 3. Compute the position of the center point of the screen.
/// @note 4. Modify U and V vectors to match the size and aspect ratio.
/// @param camera
void	update_cam_geomet(t_camera *camera)
{
	t_nml_mat	*smult_tmp;

	camera->v_align_vect = nml_mat_sub(camera->v_cam_lookat, \
		camera->v_cam_pos);
	nml_mat_normalize_r(camera->v_align_vect);
	camera->v_proj_scr_u = vect_cross(camera->v_align_vect, camera->v_cam_up);
	nml_mat_normalize_r(camera->v_proj_scr_u);
	camera->v_proj_scr_v = vect_cross(camera->v_proj_scr_u, \
		camera->v_align_vect);
	nml_mat_normalize_r(camera->v_proj_scr_v);
	smult_tmp = nml_mat_smult(camera->v_align_vect, camera->cam_len);
	camera->v_proj_scr_cen = nml_mat_add_r(camera->v_cam_pos, smult_tmp);
	nml_mat_free(smult_tmp);
	nml_mat_smult_r(camera->v_proj_scr_u, camera->cam_hor_size);

}
