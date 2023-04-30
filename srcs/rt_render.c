/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/30 22:49:54 by nnakarac         ###   ########.fr       */
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
}

int	scene_render(t_handle *handy)
{
	t_scene		scn;
	int			x;
	int			y;

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
