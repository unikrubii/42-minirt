/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_get_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:57:29 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 21:00:47 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"

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
