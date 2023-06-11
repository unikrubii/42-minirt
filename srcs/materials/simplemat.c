/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplemat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 09:58:28 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/11 23:04:53 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

// function to compute the color of the material
void	simple_compute_color(t_handle *handy, t_objbase *obj, t_scene *scn)
{
	t_nml_mat	*vtmp1;
	t_nml_mat	*vtmp2;
	(void) handy;
	(void) obj;
	(void) scn;
	// Define an initial material color
	compute_diffuse_color(handy, obj, scn);

	// Compute the reflection component.
	if (obj->material->reflectivity > 0.0)
		compute_reflect_color(handy, obj, scn);

	vtmp1 = nml_mat_smult(scn->ref_color, obj->material->reflectivity);
	vtmp2 = nml_mat_smult(scn->dif_color, (1 - obj->material->reflectivity));
	nml_mat_add_r(vtmp1, vtmp2);
	nml_mat_add_r(scn->mat_color, vtmp1);
	nml_mat_free(vtmp1);
	nml_mat_free(vtmp2);

	// compute the specular component
	if (obj->material->shiness > 0.0)
		simple_compute_specular(handy, obj, scn);

	// add the specular component to the final color
	nml_mat_add_r(scn->mat_color, scn->spc_color);
}

void	simple_spc_inter_chk(t_lightbase *light, t_handle *handy, t_objbase *obj, t_scene *scn)
{
	t_nml_mat	*v_light_dir;
	t_nml_mat	*start_point;
	t_nml_mat	*v_tmp;
	t_ray		*light_ray;
	t_scene		spc_scn;
	int			valid_int;
	t_objbase	*p_obj;

	t_nml_mat	*d;
	t_nml_mat	*r;
	t_nml_mat	*v;
	float		dot_prod;

	light_ray = malloc(sizeof(t_ray));
	v_light_dir = nml_mat_sub(light->v_location, scn->closet_int_point);
	// v_light_dir = nml_mat_sub(light->v_location, scn->v_intpoint);
	nml_vect_normalize_r(v_light_dir);
	start_point = nml_mat_cp(scn->closet_int_point);
	// start_point = nml_mat_cp(scn->v_intpoint);
	v_tmp = nml_mat_smult(v_light_dir, 0.001);
	nml_mat_add_r(start_point, v_tmp);
	nml_mat_free(v_tmp);
	v_tmp = nml_mat_add(start_point, v_light_dir);
	ray_init(light_ray, start_point, v_tmp);
	nml_mat_free(v_tmp);
	scene_init(&spc_scn);
	spc_scn.v_intpoint = new_vector();
	spc_scn.v_lc_norm = new_vector();
	spc_scn.color = new_vector();
	spc_scn.x = scn->x;
	spc_scn.y = scn->y;
	spc_scn.norm_x = ((float) spc_scn.x * spc_scn.x_fact) - 1.0;
	spc_scn.norm_y = ((float) spc_scn.y * spc_scn.y_fact) - 1.0;
	spc_scn.red = 0.0;
	spc_scn.green = 0.0;
	spc_scn.blue = 0.0;
	spc_scn.intensity = 0.0;
	spc_scn.cam_ray = light_ray;

	p_obj = handy->objects;
	valid_int = 0;
	(void) obj;
	while (p_obj)
	{
		if (p_obj != obj)
			valid_int = p_obj->obj_test_inter_scn(p_obj, &spc_scn);
		if (valid_int)
			break;
		p_obj = p_obj->next;
	}
	if (!valid_int)
	{
		// Compute the reflection vector
		d = nml_mat_cp(light_ray->v_lab);
		v_tmp = nml_mat_smult(scn->v_lc_norm, 2 * nml_vect_dot(d, 0, scn->v_lc_norm, 0));
		r = nml_mat_sub(d, v_tmp);
		nml_mat_normalize_r(r);
		nml_mat_free(v_tmp);

		// compute the dot product
		v = nml_mat_cp(scn->cam_ray->v_lab);
		nml_mat_normalize_r(v);
		dot_prod = nml_vect_dot(r, 0, v, 0);

		// Only proceed if the dot product is positive
		if (dot_prod > 0.0)
		{
			spc_scn.intensity = obj->material->reflectivity * powf(dot_prod, obj->material->shiness);
		}
	}
	// scn->spc_color->data[0][0] += light->v_color->data[0][0] * spc_scn.intensity;
	// scn->spc_color->data[1][0]  += light->v_color->data[1][0] * spc_scn.intensity;
	// scn->spc_color->data[2][0] += light->v_color->data[2][0] * spc_scn.intensity;
	// scn->red += obj->material->v_base_color->data[0][0] * spc_scn.intensity;
	// scn->green  += obj->material->v_base_color->data[1][0] * spc_scn.intensity;
	// scn->blue += obj->material->v_base_color->data[2][0] * spc_scn.intensity;
	scn->red += light->v_color->data[0][0] * spc_scn.intensity;
	scn->green  += light->v_color->data[1][0] * spc_scn.intensity;
	scn->blue += light->v_color->data[2][0] * spc_scn.intensity;
}

void	simple_compute_specular(t_handle *handy, t_objbase *obj, t_scene *scn)
{
	t_lightbase	*p_light;

	p_light = handy->lights;
	while (p_light)
	{
		// check for the intersection with all objects in the scene, except the current one;
		simple_spc_inter_chk(p_light, handy, obj, scn);
		p_light = p_light->next;
	}
	set_vect(scn->spc_color, scn->red, scn->green, scn->blue);
}
