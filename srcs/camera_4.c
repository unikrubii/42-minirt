/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:21:00 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/18 15:22:10 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "v_util.h"

float	cam_get_length(t_camera *camera)
{
	return (camera->cam_len);
}

float	cam_get_hor_size(t_camera *camera)
{
	return (camera->cam_hor_size);
}

float	cam_get_aspr(t_camera *camera)
{
	return (camera->cam_aspr);
}
