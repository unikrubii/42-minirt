/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:06:09 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/18 15:20:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "v_util.h"

t_nml_mat	cam_get_pos(t_camera *camera)
{
	return (*(camera->v_cam_pos));
}

t_nml_mat	cam_get_lookat(t_camera *camera)
{
	return (*(camera->v_cam_lookat));
}

t_nml_mat	cam_get_up(t_camera *camera)
{
	return (*(camera->v_cam_up));
}
