/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:07:16 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/20 23:15:24 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "nml_matrix.h"
# include "camera.h"
# include "ray.h"

typedef struct s_scene
{
	t_ray		*cam_ray;
	t_nml_mat	*v_intpoint;
	t_nml_mat	*v_lc_norm;
	t_nml_mat	*v_lc_color;
	float		x_fact;
	float		y_fact;
	float		min_dist;
	float		max_dist;
	float		norm_x;
	float		norm_y;
	int			valid_inter;
	float		dist;
	float		intensity;
	t_nml_mat	*color;
	int			valid_illum;
	int			x;
	int			y;
}	t_scene;

#endif
