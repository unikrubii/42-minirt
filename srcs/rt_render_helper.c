/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 22:58:43 by sthitiku          #+#    #+#             */
/*   Updated: 2023/06/17 11:25:39 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief scene init helper
/// @param scn scene ptr
void	scene_init2(t_scene *scn)
{
	scn->mat_color = new_vector();
	scn->dif_color = new_vector();
	scn->ref_color = new_vector();
	scn->spc_color = new_vector();
}

/// @brief scene initialization
/// @param scn scene ptr
void	scene_init(t_scene *scn)
{
	scn->v_intpoint = new_vector();
	scn->v_lc_norm = new_vector();
	scn->v_lc_color = new_vector();
	scn->x_fact = 1.0 / ((float) WIDTH / 2.0);
	scn->y_fact = 1.0 / ((float) HEIGHT / 2.0);
	scn->min_dist = 1e6;
	scn->max_dist = 0.0;
	scn->norm_x = 0.0;
	scn->norm_y = 0.0;
	scn->cam_ray = NULL;
	scn->dist = 0.0;
	scn->intensity = 0.0;
	scn->color = new_vector();
	scn->red = 0.0;
	scn->green = 0.0;
	scn->blue = 0.0;
	scn->valid_illum = 0;
	scn->valid_inter = 0;
	scn->illum_found = 0;
	scn->inter_found = 0;
	scn->closet_int_point = NULL;
	scn->closet_lc_color = NULL;
	scn->closet_lc_normal = NULL;
	scene_init2(scn);
}

/// @brief scene deinitialization
/// @param scn scene ptr
void	scene_deinit(t_scene *scn)
{
	nml_mat_free(scn->v_intpoint);
	nml_mat_free(scn->v_lc_norm);
	nml_mat_free(scn->v_lc_color);
	nml_mat_free(scn->color);
	nml_mat_free(scn->mat_color);
	nml_mat_free(scn->dif_color);
	nml_mat_free(scn->ref_color);
	nml_mat_free(scn->spc_color);
	if (scn->closet_int_point)
		nml_mat_free(scn->closet_int_point);
	if (scn->closet_lc_color)
		nml_mat_free(scn->closet_lc_color);
	if (scn->closet_lc_normal)
		nml_mat_free(scn->closet_lc_normal);
}
