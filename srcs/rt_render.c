/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/04 18:56:31 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	intersect_put(t_scene *scn, t_handle *handy, t_objbase *p_obj)
{
	t_nml_mat	*vtmp;
	t_lightbase	*p_light;

	p_light = handy->lights;
	while (p_light)
	{
		scn->valid_illum = p_light->light_comp_illum_scn(p_light, \
			handy->objects, p_obj, scn);
		p_light = p_light->next;
	}
	vtmp = nml_mat_sub(scn->v_intpoint, scn->cam_ray->v_point1);
	scn->dist = nml_vect_norm(vtmp);
	if (scn->valid_illum)
		my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
			((int)(p_obj->v_base_color->data[0][0] * scn->intensity) << 16) \
			+ ((int)(p_obj->v_base_color->data[1][0] * scn->intensity) << 8) \
			+ ((int)(p_obj->v_base_color->data[2][0] * scn->intensity)));
	else
		my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
			((int)0 << 16) + ((int)0 << 8) + ((int)0));
	nml_mat_free(vtmp);
}

static void	scene_pixel_put(t_scene *scn, t_handle *handy, t_objbase *p_obj)
{
	t_nml_mat	*vtmp;
	t_lightbase	*p_light;
	t_objbase	*closet_obj;

	p_light = handy->lights;
	closet_obj = NULL;
	scn->min_dist = 1e6;
	scn->inter_found = 0;
	scn->valid_inter = 0;
	scn->debug = 0;
	while (p_obj)
	{
		scn->valid_inter = p_obj->obj_test_inter_scn(p_obj, scn);
		if (scn->valid_inter)
		{
			// compute the flag to indicate that we found an intersection
			scn->inter_found = 1;

			// Compute the distance between the camere and the point of intersection
			vtmp = nml_mat_sub(scn->v_intpoint, scn->cam_ray->v_point1);
			scn->dist = nml_vect_norm(vtmp);
			nml_mat_free(vtmp);
			// if (scn->min_dist < 10000)
			// {
			// 	scn->debug = 1;
			// 	// dprintf(2, "obj:%d\tdist:%f\tmin_dist:%f\t%f\n", p_obj->type, scn->dist, scn->min_dist, p_obj->v_base_color->data[2][0]);
			// }
			if (scn->dist <= scn->min_dist)
			{
				scn->min_dist = scn->dist;
				closet_obj = p_obj;
				// scn->closet_int_point = scn->v_intpoint;
				// scn->closet_lc_normal = scn->v_lc_norm;
				// scn->closet_lc_color = scn->v_lc_color;
				// scn->closet_lc_color = closet_obj->v_base_color;
				scn->closet_int_point = nml_mat_cp(scn->v_intpoint);
				scn->closet_lc_normal = nml_mat_cp(scn->v_lc_norm);
				scn->closet_lc_color = nml_mat_cp(scn->v_lc_color);
			}
		}
		p_obj = p_obj->next;
	}

	// Compute the illumination for the closet object, assuming that there was a valid intersection
	if (scn->inter_found)
	{
		// scn->red = scn->closet_lc_color->data[0][0] * 255;
		// scn->green = scn->closet_lc_color->data[1][0] * 255;
		// scn->blue = scn->closet_lc_color->data[2][0] * 255;
		// 	my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
		// 	((int)(scn->red) << 16) \
		// 	+ ((int)(scn->green) << 8) \
		// 	+ ((int)(scn->blue)));
		// Compute the intensity of illumination
		scn->red = 0;
		scn->green = 0;
		scn->blue = 0;
		scn->valid_illum = 0;
		scn->illum_found = 0;
		while (p_light)
		{
			scn->valid_illum = p_light->light_comp_illum_scn(p_light, \
				handy->objects, closet_obj, scn);
			if (scn->valid_illum)
			{
				scn->illum_found = 1;
				// scn->red += scn->color->data[0][0] * scn->intensity;
				// scn->green += scn->color->data[1][0] * scn->intensity;
				// scn->blue += scn->color->data[2][0] * scn->intensity;
				scn->red += scn->color->data[0][0] * scn->intensity;
				scn->green += scn->color->data[1][0] * scn->intensity;
				scn->blue += scn->color->data[2][0] * scn->intensity;
			}
			p_light = p_light->next;
		}
		if (scn->illum_found)
		{
			scn->red *= scn->closet_lc_color->data[0][0];
			scn->green *= scn->closet_lc_color->data[1][0];
			scn->blue *= scn->closet_lc_color->data[2][0];
			my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
			((int)(scn->red) << 16) \
			+ ((int)(scn->green) << 8) \
			+ ((int)(scn->blue)));
		}
		// else
		// {
		// 	my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
		// 	((int)(0) << 16) \
		// 	+ ((int)(0) << 8) \
		// 	+ ((int)(0)));
		// }

	}

	// while (p_obj)
	// {
	// 	scn->valid_inter = p_obj->obj_test_inter_scn(p_obj, scn);
	// 	if (scn->valid_inter)
	// 		intersect_put(scn, handy, p_obj);
	// 	// else
	// 	// 	my_mlx_pixel_put(&handy->data.img, scn->x, scn->y, \
	// 	// 		((int)0 << 16) + ((int)0 << 8) + ((int)0));
	// 	p_obj = p_obj->next;
	// }

}

// t_ray		*cam_ray;
// 	t_nml_mat	*v_intpoint;
// 	t_nml_mat	*v_lc_norm;
// 	t_nml_mat	*v_lc_color;
// 	float		x_fact;
// 	float		y_fact;
// 	float		min_dist;
// 	float		max_dist;
// 	float		norm_x;
// 	float		norm_y;
// 	int			valid_inter;
// 	float		dist;
// 	float		intensity;
// 	t_nml_mat	*color;
// 	int			valid_illum;
// 	int			x;
// 	int			y;
// 	t_nml_mat	*closet_int_point;
// 	t_nml_mat	*closet_lc_normal;
// 	t_nml_mat	*closet_lc_color;
// 	int			inter_found;
// 	float		red;
// 	float		green;
// 	float		blue;
// 	int			illum_found;

void	debug_scene_init(t_scene *scn)
{
	scn->x_fact = 1.0 / ((float) WIDTH / 2.0);
	scn->y_fact = 1.0 / ((float) HEIGHT / 2.0);
	scn->min_dist = 1e6;
	scn->max_dist = 0.0;
	scn->norm_x = 0.0;
	scn->norm_y = 0.0;
	scn->cam_ray = NULL;
	// scn->bck_ray = NULL;
	scn->dist = 0.0;
	scn->intensity = 0.0;
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
	scn->color = new_vector();
	// scn->v_poi = new_vector();
	// scn->v_obj_org = new_vector();
	// set_vect(scn->v_obj_org, 0.0, 0.0, 0.0);
}

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
			scn.norm_x = ((float) scn.x * scn.x_fact) - 1.0;
			scn.norm_y = ((float) scn.y * scn.y_fact) - 1.0;
			// scn.closet_int_point = NULL;
			// scn.closet_lc_normal = NULL;
			// scn.closet_lc_color = NULL;
			if (scn.closet_int_point)
			{
				nml_mat_free(scn.closet_int_point);
				scn.closet_int_point = NULL;
			}
			if (scn.closet_lc_normal)
			{
				nml_mat_free(scn.closet_lc_normal);
				scn.closet_lc_normal = NULL;
			}
			if (scn.closet_lc_color)
			{
				nml_mat_free(scn.closet_lc_color);
				scn.closet_lc_color = NULL;
			}
			scn.cam_ray = generate_ray(handy->camera, scn.norm_x, scn.norm_y);
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

void	find_max_color_util(t_handle *handy, int color)
{
	float	red;
	float	green;
	float	blue;

	red = (color & 0xFF0000) >> 16;
	green = (color & 0xFF00) >> 8;
	blue = color & 0xFF;
	if (red > handy->max_red)
		handy->max_red = red;
	if (green > handy->max_green)
		handy->max_green = green;
	if (blue > handy->max_blue)
		handy->max_blue = blue;
	if (handy->max_red > handy->maxall)
		handy->maxall = red;
	if (handy->max_green > handy->maxall)
		handy->maxall = green;
	if (handy->max_blue > handy->maxall)
		handy->maxall = blue;
}

void	find_max_color(t_handle *handy)
{
	int		x;
	int		y;
	int		color;
	char	*dst;


	x = 0;
	y = 0;

	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			dst = handy->data.img.addr + (y * handy->data.img.line_length + x * (handy->data.img.bits_per_pixel / 8));
			color = *(unsigned int *) dst;
			find_max_color_util(handy, color);
			y++;
		}
		x++;
	}
}

void	set_new_color(t_handle *handy)
{
	int		x;
	int		y;
	int		color;
	char	*dst;
	float	red;
	float	green;
	float	blue;

	x = 0;
	y = 0;

	while (x < WIDTH)
	{
		y = 0;
		color = 0;
		while (y < HEIGHT)
		{
			dst = handy->data.img.addr + (y * handy->data.img.line_length + x * (handy->data.img.bits_per_pixel / 8));
			red = (((color & 0xFF0000) >> 16) / handy->maxall) * 255.0;
			green = (((color & 0xFF00) >> 8)  / handy->maxall) * 255.0;
			blue = ((color & 0xFF)  / handy->maxall) * 255.0;

			*(unsigned int *) dst = ((int)(red) << 16) + ((int)(green) << 8) + ((int)(blue));

			y++;
		}
		x++;
	}
}

int	render(t_handle *handy)
{
	if (handy->data.win == NULL)
		return (1);
	scene_render(handy);
	// remap color of every pixel
	// 1. calculate max value
	// find_max_color(handy);
	// 2. remap the
	// set_new_color(handy);
	// done
	mlx_put_image_to_window(handy->data.mlx, handy->data.win, \
		handy->data.img.img, 0, 0);
	return (0);
}
