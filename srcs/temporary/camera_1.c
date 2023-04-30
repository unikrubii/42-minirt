/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 08:10:41 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 22:06:31 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "v_util.h"

void	camera_init(t_camera *camera)
{
	camera->v_cam_pos = nml_mat_new(3, 1);
	camera->v_cam_lookat = nml_mat_new(3, 1);
	camera->v_cam_up = nml_mat_new(3, 1);
	set_vect(camera->v_cam_pos, 0.0, -10.0, 0.0);
	set_vect(camera->v_cam_lookat, 0.0, 0.0, 0.0);
	set_vect(camera->v_cam_up, 0.0, 0.0, 1.0);
	camera->cam_len = 1.0;
	camera->cam_hor_size = 1.0;
	camera->cam_aspr = 1.0;
}

void	cam_set_pos(t_camera *camera, float u, float v, float w)
{
	set_vect(camera->v_cam_pos, u, v, w);
}

void	cam_set_lookat(t_camera *camera, float u, float v, float w)
{
	set_vect(camera->v_cam_lookat, u, v, w);
}

void	cam_set_up(t_camera *camera, float u, float v, float w)
{
	set_vect(camera->v_cam_up, u, v, w);
}
