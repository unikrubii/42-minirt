/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_geomet_gen_ray.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:04:31 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 21:04:46 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"

/// @brief Function to compute camera geometry
/// @note 1. Compute a vector from the camera position to the LookAt position.
/// @note 2. Compute the U and V vectors.
/// @note 3. Compute the position of the center point of the screen.
/// @note 4. Modify U and V vectors to match the size and aspect ratio.
/// @param camera
void	update_cam_geomet(t_camera *camera)
{
	t_nml_mat	*stmp;

	camera->v_align_vect = nml_mat_sub(camera->v_cam_lookat, \
		camera->v_cam_pos);
	nml_mat_normalize_r(camera->v_align_vect);
	camera->v_proj_scr_u = vect_cross(camera->v_align_vect, camera->v_cam_up);
	nml_mat_normalize_r(camera->v_proj_scr_u);
	camera->v_proj_scr_v = vect_cross(camera->v_proj_scr_u, \
		camera->v_align_vect);
	nml_mat_normalize_r(camera->v_proj_scr_v);
	stmp = nml_mat_smult(camera->v_align_vect, camera->cam_len);
	camera->v_proj_scr_cen = nml_mat_cp(camera->v_cam_pos);
	nml_mat_add_r(camera->v_proj_scr_cen, stmp);
	nml_mat_free(stmp);
	nml_mat_smult_r(camera->v_proj_scr_u, camera->cam_hor_size);
	nml_mat_smult_r(camera->v_proj_scr_v, \
		(camera->cam_hor_size / camera->cam_aspr));
}

t_ray	*generate_ray(t_camera *camera, float pro_scr_x, float pro_scr_y)
{
	t_nml_mat	*v_scr_wrld_coord;
	t_nml_mat	*stmp;
	t_ray		*ray;

	ray = malloc(sizeof(t_ray) * 1);
	v_scr_wrld_coord = nml_mat_cp(camera->v_proj_scr_cen);
	stmp = nml_mat_smult(camera->v_proj_scr_u, pro_scr_x);
	nml_mat_add_r(v_scr_wrld_coord, stmp);
	nml_mat_free(stmp);
	stmp = nml_mat_smult(camera->v_proj_scr_v, pro_scr_y);
	nml_mat_add_r(v_scr_wrld_coord, stmp);
	nml_mat_free(stmp);
	ray_init(ray, camera->v_cam_pos, v_scr_wrld_coord);
	nml_mat_free(v_scr_wrld_coord);
	return (ray);
}
