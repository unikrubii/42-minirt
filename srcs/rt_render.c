/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 12:03:12 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scene_render(t_handle *handy)
{
	(void) handy;
	return (0);
}

int	render(t_handle *handy)
{
	if (handy->data.win == NULL)
		return (1);
	// scene_render(handy);
	// remap color of every pixel
	// 1. calculate max value
	// find_max_color(handy);
	// 2. remap the
	// set_new_color(handy);
	// done

	// mlx_put_image_to_window(handy->data.mlx, handy->data.win, \
	// 	handy->data.img.img, 0, 0);
	return (0);
}
