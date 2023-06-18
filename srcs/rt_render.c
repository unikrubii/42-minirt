/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 16:08:40 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	scene_pixel_put_util(t_scene *scn, t_objbase *p_obj, \
	t_objbase **closet_obj)
{
	t_nml_mat	*vtmp;

	while (p_obj)
	{
		scn->valid_inter = p_obj->obj_test_inter_scn(p_obj, scn);
		if (scn->valid_inter)
		{
			scn->inter_found = 1;
			vtmp = nml_mat_sub(scn->v_intpoint, scn->cam_ray->v_point1);
			scn->dist = nml_vect_norm(vtmp);
			nml_mat_free(vtmp);
			if (scn->dist <= scn->min_dist)
			{
				scn->min_dist = scn->dist;
				*closet_obj = p_obj;
				scn->closet_int_point = nml_mat_cp(scn->v_intpoint);
				scn->closet_lc_normal = nml_mat_cp(scn->v_lc_norm);
				scn->closet_lc_color = nml_mat_cp(scn->v_lc_color);
			}
		}
		p_obj = p_obj->next;
	}
}

void	scene_pixel_put(t_scene *scn, t_handle *handy, t_objbase *p_obj)
{
	t_lightbase	*p_light;
	t_objbase	*closet_obj;

	p_light = handy->lights;
	closet_obj = NULL;
	scn->min_dist = 1e6;
	scn->inter_found = 0;
	scn->valid_inter = 0;
	scene_pixel_put_util(scn, p_obj, &closet_obj);
	if (scn->inter_found)
	{
		if (closet_obj->has_material)
		{
			handy->rfl_ray_cnt = 0;
			if (closet_obj->material->type == SIM)
				simple_compute_color(handy, closet_obj, scn);
			pix_color_put_v(scn, scn->mat_color, handy);
		}
		else
		{
			compute_diffuse_color(handy, closet_obj, scn);
			pix_color_put_v(scn, scn->dif_color, handy);
		}
	}
}

/// @brief scene render utility
/// @param handy main struct ptr
/// @param scn scene ptr
void	scene_render_util(t_handle *handy, t_scene *scn)
{
	scn->norm_x = ((float) scn->x * scn->x_fact) - 1.0;
	scn->norm_y = ((float) scn->y * scn->y_fact) - 1.0;
	set_vect(scn->mat_color, 0, 0, 0);
	set_vect(scn->dif_color, 0, 0, 0);
	set_vect(scn->spc_color, 0, 0, 0);
	set_vect(scn->ref_color, 0, 0, 0);
	scn->red = 0;
	scn->green = 0;
	scn->blue = 0;
	if (scn->closet_int_point)
	{
		nml_mat_free(scn->closet_int_point);
		scn->closet_int_point = NULL;
	}
	if (scn->closet_lc_normal)
	{
		nml_mat_free(scn->closet_lc_normal);
		scn->closet_lc_normal = NULL;
	}
	if (scn->closet_lc_color)
	{
		nml_mat_free(scn->closet_lc_color);
		scn->closet_lc_color = NULL;
	}
	scn->cam_ray = generate_ray(handy->camera, scn->norm_x, scn->norm_y);
}

/// @brief scene render function
/// @note 1 - scene init
/// @note 2 - render every pixel and put color
/// @note 3 - scene deinit
/// @param handy
/// @return
int	scene_render(t_handle *handy)
{
	t_scene		scn;
	t_objbase	*p_obj;

	scene_init(&scn);
	scn.x = 0;
	while (scn.x < WIDTH)
	{
		scn.y = 0;
		while (scn.y < HEIGHT)
		{
			scene_render_util(handy, &scn);
			p_obj = handy->objects;
			scene_pixel_put(&scn, handy, p_obj);
			scn.y++;
			ray_deinit(scn.cam_ray);
		}
		scn.x++;
	}
	scene_deinit(&scn);
	return (1);
}

/// @brief main render function
/// @note 1 - render scene
/// @note 2 - pixel color optimization
/// @note 3 - put image to window
/// @param handy main struct ptr
/// @return
int	render(t_handle *handy)
{
	if (handy->data.win == NULL)
		return (1);
	scene_render(handy);
	opt_color(handy);
	mlx_put_image_to_window(handy->data.mlx, handy->data.win, \
		handy->data.img.img, 0, 0);
	return (0);
}
