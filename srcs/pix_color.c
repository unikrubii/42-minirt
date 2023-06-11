/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:43:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/11 15:49:03 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	opt_color(t_handle *handy)
{
	int			width;
	int			height;
	t_nml_mat	**dst;

	width = 0;
	height = 0;
	while (width < WIDTH)
	{
		height = 0;
		while (height < HEIGHT)
		{
			dst = handy->vv_color + (HEIGHT * width) + (height);
			(*dst)->data[0][0] = (*dst)->data[0][0] / handy->maxall * 255;
			(*dst)->data[1][0] = (*dst)->data[1][0] / handy->maxall * 255;
			(*dst)->data[2][0] = (*dst)->data[2][0] / handy->maxall * 255;
			my_mlx_pixel_put(&handy->data.img, width, height, \
				((int)(*dst)->data[0][0] << 16) + ((int)(*dst)->data[1][0] << 8) \
				+ ((int)(*dst)->data[2][0]));
			height++;
		}
		width++;
	}
}

void	init_color_pix(t_handle *handy)
{
	int			width;
	int			height;
	t_nml_mat	**dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	width = 0;
	height = 0;
	// init all pixel color
	handy->max_red = 0.0;
	handy->max_green = 0.0;
	handy->max_blue = 0.0;
	handy->maxall = 0.0;
	handy->vv_color = malloc(sizeof(t_nml_mat *) * WIDTH * HEIGHT);
	while (width < WIDTH)
	{
		height = 0;
		while (height < HEIGHT)
		{
			dst = handy->vv_color + (HEIGHT * width) + (height);
			*dst = new_vector();
			height++;
		}
		width++;
	}
}

void	deinit_color_pix(t_handle *handy)
{
	int			width;
	int			height;
	t_nml_mat	**dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	width = 0;
	height = 0;
	while (width < WIDTH)
	{
		height = 0;
		while (height < HEIGHT)
		{
			dst = handy->vv_color + (HEIGHT * width) + (height);
			nml_mat_free(*dst);
			height++;
		}
		width++;
	}
	free(handy->vv_color);
}


void	pix_color_put(t_scene *scn, t_handle *handy)
{
	t_nml_mat	**dst;

	dst = handy->vv_color + (HEIGHT * scn->x) + (scn->y);
	(*dst)->data[0][0] = scn->red;
	(*dst)->data[1][0] = scn->green;
	(*dst)->data[2][0] = scn->blue;
	if (scn->red > handy->max_red)
		handy->max_red = scn->red;
	if (scn->green > handy->max_green)
		handy->max_green = scn->green;
	if (scn->blue > handy->max_blue)
		handy->max_blue = scn->blue;
	if (handy->max_red > handy->maxall)
		handy->maxall = scn->red;
	if (handy->max_green > handy->maxall)
		handy->maxall = scn->green;
	if (handy->max_blue > handy->maxall)
		handy->maxall = scn->blue;
}

void	pix_color_put_v(t_scene *scn, t_nml_mat *v_color, t_handle *handy)
{
	t_nml_mat	**dst;

	dst = handy->vv_color + (HEIGHT * scn->x) + (scn->y);
	(*dst)->data[0][0] = v_color->data[0][0];
	(*dst)->data[1][0] = v_color->data[1][0];
	(*dst)->data[2][0] = v_color->data[2][0];
	if (v_color->data[0][0] > handy->max_red)
		handy->max_red = v_color->data[0][0];
	if (v_color->data[1][0] > handy->max_green)
		handy->max_green = v_color->data[1][0];
	if (v_color->data[2][0] > handy->max_blue)
		handy->max_blue = v_color->data[2][0];
	if (handy->max_red > handy->maxall)
		handy->maxall = v_color->data[0][0];
	if (handy->max_green > handy->maxall)
		handy->maxall = v_color->data[1][0];
	if (handy->max_blue > handy->maxall)
		handy->maxall = v_color->data[2][0];
}
