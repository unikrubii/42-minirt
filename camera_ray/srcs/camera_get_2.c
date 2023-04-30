/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_get_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 21:01:14 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 21:02:47 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"

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
