/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 15:29:38 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/23 17:10:31 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
#include "v_util.h"

/// @brief Method to return U vector.
/// @param camera
/// @return
t_nml_mat	cam_get_scr_u(t_camera *camera)
{
	return (*(camera->v_proj_scr_u));
}

/// @brief Method to return V vector.
/// @param camera
/// @return
t_nml_mat	cam_get_scr_v(t_camera *camera)
{
	return (*(camera->v_proj_scr_v));
}

/// @brief Metod to return the projection screen center
/// @param camera
/// @return
t_nml_mat	cam_get_scr_cen(t_camera *camera)
{
	return (*(camera->v_proj_scr_cen));
}
