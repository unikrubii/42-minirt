/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_set_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 20:37:09 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 21:42:43 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "ray.h"

/// @brief Set camera length
/// @param camera
/// @param len
void	cam_set_length(t_camera *camera, float len)
{
	camera->cam_len = len;
}

/// @brief Set camera horizontal size
/// @param camera
/// @param size
void	cam_set_hor_size(t_camera *camera, float size)
{
	camera->cam_hor_size = size;
}

/// @brief Set camera aspect ratio
/// @note
/// @param camera
/// @param ratio
void	cam_set_aspr(t_camera *camera, float ratio)
{
	camera->cam_aspr = ratio;
}
