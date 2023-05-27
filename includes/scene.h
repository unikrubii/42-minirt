/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:07:16 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/27 12:21:26 by nnakarac         ###   ########.fr       */
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
	t_objbase	*closet_obj;
	t_nml_mat	*closet_int_point;
	t_nml_mat	*closet_lc_normal;
	t_nml_mat	*closet_lc_color;
	float		min_dist;
	int			inter_found;
	float		dist;
	float		red;
	float		green;
	float		blue;
	int			illum_found;
}	t_scene;

#endif
