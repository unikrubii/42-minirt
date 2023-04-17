/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:31:00 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/17 17:12:29 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_key_close(t_handle *handy)
{
	mlx_clear_window(handy->data.mlx, handy->data.win);
	mlx_destroy_window(handy->data.mlx, handy->data.win);
	handy->data.mlx = NULL;
	handy->data.mlx = NULL;
	exit(0);
}

int	mlx_close(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_window(vars->mlx, vars->win);
	vars->win = NULL;
	vars->mlx = NULL;
	exit(0);
}

int	rt_key_handler(int keycode, t_handle *handy)
{
	if (keycode == KEY_ESC)
		mlx_key_close(handy);
	else
		mlx_re_draw(handy);
	return (0);
}
