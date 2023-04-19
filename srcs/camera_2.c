/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 14:58:01 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/18 14:58:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "v_util.h"

void	cam_set_length(t_camera *camera, float len)
{
	camera->cam_len = len;
}

void	cam_set_hor_size(t_camera *camera, float size)
{
	camera->cam_hor_size = size;
}

void	cam_set_aspr(t_camera *camera, float ratio)
{
	camera->cam_aspr = ratio;
}
