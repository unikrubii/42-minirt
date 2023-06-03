/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pix_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 12:43:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 12:44:32 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_color_pix(t_handle *handy)
{
	int			width;
	int			height;
	t_nml_mat	**dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	width = 0;
	height = 0;
	// init all pixel color
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
