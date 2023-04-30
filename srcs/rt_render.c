/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/01 01:26:46 by nnakarac         ###   ########.fr       */
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
			// Test if we have a valid intersection
			scn.valid_inter = handy->objects->obj_test_intersect(scn.cam_ray, \
				scn.v_intpoint, scn.v_lc_norm, scn.v_lc_color);
			if (scn.valid_inter)
			{
				//compute distance between camera and the point of intersection
				vtmp = nml_mat_sub(scn.v_intpoint, scn.cam_ray->v_point1);
				scn.dist = nml_vect_dot(vtmp, 0, vtmp, 0);
				// printf("dist: %f\n", scn.dist);
				my_mlx_pixel_put(&handy->data.img, x, y, ((int) (255.0 - ((scn.dist - 9.0) / 0.94605) * 255.0 ) << 16) + ((int) 0 << 8) + ((int) 0 ));
				// my_mlx_pixel_put(&handy->data.img, x, y, ((int) (255) << 16) + ((int) 0 << 8) + ((int) 0 ));
				nml_mat_free(vtmp);
			}
			else
				my_mlx_pixel_put(&handy->data.img, x, y, ((int) 0 << 16) + ((int) 0 << 8) + ((int) 0 ));
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
