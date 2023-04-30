/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 09:30:11 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scene_render(t_handle *handy)
{
	t_ray		*cam_ray;
	t_nml_mat	*v_intpoint;
	t_nml_mat	*v_lc_norm;
	t_nml_mat	*v_lc_color;

	float		x_fact;
	float		y_fact;
	float		min_dist;
	float		max_dist;

	int			x;
	int			y;

	float		norm_x;
	float		norm_y;

	int			valid_inter;

	v_intpoint = nml_mat_new(3, 1);
	v_lc_norm = nml_mat_new(3, 1);
	v_lc_color = nml_mat_new(3, 1);
	x_fact = 1.0 / ((float) WIDTH / 2.0);
	y_fact = 1.0 / ((float) HEIGHT / 2.0);
	min_dist = 1e6;
	max_dist = 0.0;
	x = 0;
	norm_x = 0.0;
	norm_y = 0.0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			// Normalize x and y coordinate
			norm_x = ((float) x * x_fact) - 1.0;
			norm_y = ((float) y * y_fact) - 1.0;

			//Generate the ray for this pixel
			cam_ray = generate_ray(handy->camera, norm_x, norm_y);

			// Test if we have a valid intersection
			valid_inter = handy->objects->obj_test_intersect(cam_ray, \
				v_intpoint, v_lc_norm, v_lc_color);

			if (valid_inter)
				my_mlx_pixel_put(&handy->data.img, x, y, ((int) 255 << 16) + ((int) 0 << 8) + ((int) 0 ));
			else
				my_mlx_pixel_put(&handy->data.img, x, y, ((int) 0 << 16) + ((int) 0 << 8) + ((int) 0 ));
			y++;
		}
		x++;
	}
	return (1);
}

int	render(t_handle *handy)
{
	if (handy->data.win == NULL)
		return (1);
	// mlx_draw(&handy->data.img, &handy->draw);
	scene_render(handy);
	mlx_put_image_to_window(handy->data.mlx, handy->data.win, \
		handy->data.img.img, 0, 0);
	return (0);
}
