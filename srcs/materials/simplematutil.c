/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplematutil.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 09:43:04 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/24 13:25:31 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

/// @brief function to compute the color of the material
/// @note 1 - Define an initial material color
/// @note 2 - Compute the reflection component.
/// @note 3 - compute the specular component
/// @note 4 - add the specular component to the final color
/// @param handy
/// @param obj
/// @param scn
void	simple_compute_color(t_handle *handy, t_objbase *obj, \
	t_scene *scn)
{
	t_nml_mat	*vtmp1;
	t_nml_mat	*vtmp2;
	t_scene		rfl_scn;

	scene_init(&rfl_scn);
	compute_diffuse_color(handy, obj, scn);
	if (obj->material->reflectivity > 0.0)
		compute_reflect_color(handy, obj, scn, &rfl_scn);
	vtmp1 = nml_mat_smult(scn->ref_color, obj->material->reflectivity);
	vtmp2 = nml_mat_smult(scn->dif_color, (1 - obj->material->reflectivity));
	nml_mat_add_r(vtmp1, vtmp2);
	nml_mat_add_r(scn->mat_color, vtmp1);
	nml_mat_free(vtmp1);
	nml_mat_free(vtmp2);
	if (obj->material->shiness > 0.0)
		simple_compute_specular(handy, obj, scn);
	nml_mat_add_r(scn->mat_color, scn->spc_color);
}
