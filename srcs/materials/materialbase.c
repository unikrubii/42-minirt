/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materialbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:54:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/24 01:10:30 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

/// @brief material base initialization
/// @param mat
void	mat_init(t_matbase *mat)
{
	(void) mat;
	mat->v_base_color = new_vector();
	set_vect(mat->v_base_color, 1.0, 0.0, 1.0);
	mat->shiness = 0.0;
	mat->reflectivity = 0.0;
}

/// @brief material base deinitialization
/// @param mat
void	mat_deinit(t_matbase *mat)
{
	(void) mat;
	nml_mat_free(mat->v_base_color);
}

/// @brief base function to compute the color of the material
/// @param handy
/// @param closet_obj
/// @param scn
void	compute_color(t_handle *handy, t_objbase *closet_obj, t_scene *scn)
{
	(void) handy;
	(void) closet_obj;
	(void) scn;
}

/// @brief compute diffuse color util
/// @note set scene color
/// @param scn
void	compute_diffuse_color_util(t_scene *scn)
{
	if (scn->illum_found)
	{
		scn->red *= scn->closet_lc_color->data[0][0];
		scn->green *= scn->closet_lc_color->data[1][0];
		scn->blue *= scn->closet_lc_color->data[2][0];
		set_vect(scn->dif_color, scn->red, scn->green, scn->blue);
	}
}

/// @brief compute diffuse color
/// @param handy
/// @param closet_obj
/// @param scn
void	compute_diffuse_color(t_handle *handy, t_objbase *closet_obj, \
	t_scene *scn)
{
	t_lightbase	*p_light;

	scn->red = 0;
	scn->green = 0;
	scn->blue = 0;
	scn->valid_illum = 0;
	scn->illum_found = 0;
	p_light = handy->lights;
	while (p_light)
	{
		scn->valid_illum = p_light->light_comp_illum_scn(p_light, \
			handy->objects, closet_obj, scn);
		if (scn->valid_illum)
		{
			scn->illum_found = 1;
			scn->red += scn->color->data[0][0] * scn->intensity;
			scn->green += scn->color->data[1][0] * scn->intensity;
			scn->blue += scn->color->data[2][0] * scn->intensity;
		}
		p_light = p_light->next;
	}
	compute_diffuse_color_util(scn);
}
