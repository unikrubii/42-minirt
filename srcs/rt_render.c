/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/13 17:55:09 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
}

void	scene_deinit(t_scene *scn)
{
	nml_mat_free(scn->v_intpoint);
	nml_mat_free(scn->v_lc_norm);
	nml_mat_free(scn->v_lc_color);
}

int	scene_render(t_handle *handy)
{
	t_scene		scn;
	int			x;
	int			y;
	t_nml_mat	*vtmp;
	t_objbase	*p_obj;
	t_lightbase	*p_light;

	scene_init(&scn);
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// Normalize x and y coordinate
			scn.norm_x = ((float) x * scn.x_fact) - 1.0;
			scn.norm_y = ((float) y * scn.y_fact) - 1.0;
			//Generate the ray for this pixel
			scn.cam_ray = generate_ray(handy->camera, scn.norm_x, scn.norm_y);
			p_obj = handy->objects;
			while (p_obj)
			{
				scn.valid_inter = p_obj->obj_test_inter_scn(&scn);
				if (scn.valid_inter)
				{
					p_light = handy->lights;
					while (p_light)
					{
						scn.valid_illum = p_light->light_comp_illum_scn(p_light, handy->objects, p_obj, &scn);
						p_light = p_light->next;
					}
					//compute distance between camera and the point of intersection
					vtmp = nml_mat_sub(scn.v_intpoint, scn.cam_ray->v_point1);
					scn.dist = nml_vect_norm(vtmp);
					if (scn.valid_illum)
					{
						my_mlx_pixel_put(&handy->data.img, x, y, ((int) (255.0 * scn.intensity) << 16) + ((int) 0 << 8) + ((int) 0 ));
					}
					else
					{
						my_mlx_pixel_put(&handy->data.img, x, y, ((int) 0 << 16) + ((int) 0 << 8) + ((int) 0 ));
					}
					nml_mat_free(vtmp);
				}
				else
					my_mlx_pixel_put(&handy->data.img, x, y, ((int) 0 << 16) + ((int) 0 << 8) + ((int) 0 ));
				p_obj = p_obj->next;
			}
			y++;
			ray_deinit(scn.cam_ray);
			scn.cam_ray = NULL;
		}
		x++;
	}
	scene_deinit(&scn);
	return (1);
}

int	render(t_handle *handy)
{
	if (handy->data.win == NULL)
		return (1);
	// mlx_draw(&handy->data.img, &handy->draw);
	scene_render(handy);
	// sleep(1);
	mlx_put_image_to_window(handy->data.mlx, handy->data.win, \
		handy->data.img.img, 0, 0);
	return (0);
}
