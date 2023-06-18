/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplemat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 09:58:28 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/18 09:45:20 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

/// @brief simple material intersection util
/// @note test valid intersection
/// @param handy
/// @param obj
/// @param spc_scn
/// @return valid intersection flag 1 - valid, 0 - invalid
int	simple_spc_inter_chk_util2(t_handle *handy, t_objbase *obj, \
	t_scene *spc_scn)
{
	int			valid_int;
	t_objbase	*p_obj;

	p_obj = handy->objects;
	valid_int = 0;
	while (p_obj)
	{
		if (p_obj != obj)
			valid_int = p_obj->obj_test_inter_scn(p_obj, spc_scn);
		if (valid_int)
			break ;
		p_obj = p_obj->next;
	}
	return (valid_int);
}

/// @brief simple material intersection check util
/// @note initialize the specular scene
/// @param spc_scn
/// @param scn
/// @param light_ray
void	simple_spc_inter_chk_util(t_scene *spc_scn, t_scene *scn, \
	t_ray *light_ray)
{
	scene_init(spc_scn);
	spc_scn->v_intpoint = new_vector();
	spc_scn->v_lc_norm = new_vector();
	spc_scn->color = new_vector();
	spc_scn->x = scn->x;
	spc_scn->y = scn->y;
	spc_scn->norm_x = ((float) spc_scn->x * spc_scn->x_fact) - 1.0;
	spc_scn->norm_y = ((float) spc_scn->y * spc_scn->y_fact) - 1.0;
	spc_scn->red = 0.0;
	spc_scn->green = 0.0;
	spc_scn->blue = 0.0;
	spc_scn->intensity = 0.0;
	spc_scn->cam_ray = light_ray;
}

void	simple_spc_valid_int(t_handle *handy, t_objbase *obj, t_scene *scn, \
	t_scene *spc_scn)
{
	t_nml_mat	*v_tmp;
	t_nml_mat	*d;
	t_nml_mat	*r;
	t_nml_mat	*v;
	float		dot_prod;

	if (!simple_spc_inter_chk_util2(handy, obj, spc_scn))
	{
		d = nml_mat_cp(spc_scn->cam_ray->v_lab);
		v_tmp = nml_mat_smult(scn->v_lc_norm, 2 * \
			nml_vect_dot(d, 0, scn->v_lc_norm, 0));
		r = nml_mat_sub(d, v_tmp);
		nml_mat_normalize_r(r);
		nml_mat_free(v_tmp);
		v = nml_mat_cp(scn->cam_ray->v_lab);
		nml_mat_normalize_r(v);
		dot_prod = nml_vect_dot(r, 0, v, 0);
		if (dot_prod > 0.0)
		{
			spc_scn->intensity = obj->material->reflectivity * \
				powf(dot_prod, obj->material->shiness);
		}
	}
}

/// @brief simple material intersection check
/// @param light
/// @param handy
/// @param obj
/// @param scn
void	simple_spc_inter_chk(t_lightbase *light, t_handle *handy, \
	t_objbase *obj, t_scene *scn)
{
	t_nml_mat	*v_light_dir;
	t_nml_mat	*start_point;
	t_nml_mat	*v_tmp;
	t_ray		*light_ray;
	t_scene		spc_scn;

	light_ray = malloc(sizeof(t_ray));
	v_light_dir = nml_mat_sub(light->v_location, scn->closet_int_point);
	nml_vect_normalize_r(v_light_dir);
	start_point = nml_mat_cp(scn->closet_int_point);
	v_tmp = nml_mat_smult(v_light_dir, 0.001);
	nml_mat_add_r(start_point, v_tmp);
	nml_mat_free(v_tmp);
	v_tmp = nml_mat_add(start_point, v_light_dir);
	ray_init(light_ray, start_point, v_tmp);
	nml_mat_free(v_tmp);
	simple_spc_inter_chk_util(&spc_scn, scn, light_ray);
	spc_scn.cam_ray = light_ray;
	simple_spc_valid_int(handy, obj, scn, &spc_scn);
	scn->red += light->v_color->data[0][0] * spc_scn.intensity;
	scn->green += light->v_color->data[1][0] * spc_scn.intensity;
	scn->blue += light->v_color->data[2][0] * spc_scn.intensity;
}

/// @brief Simple Material Specular Light
/// @note check for the intersection with all objects in the scene,
/// @note except the current one;
/// @param handy
/// @param obj
/// @param scn
void	simple_compute_specular(t_handle *handy, t_objbase *obj, t_scene *scn)
{
	t_lightbase	*p_light;

	p_light = handy->lights;
	while (p_light)
	{
		simple_spc_inter_chk(p_light, handy, obj, scn);
		p_light = p_light->next;
	}
	set_vect(scn->spc_color, scn->red, scn->green, scn->blue);
}
