/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:11:39 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/12 19:11:48 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	render(t_handle *handy)
{
	if (handy->data->win == NULL)
		return (1);
	mlx_put_image_to_window(handy->data->mlx, handy->data->win, \
		handy->data->img.img, 0, 0);
	return (0);
}
