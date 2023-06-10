/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materialbase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:54:42 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/10 20:16:04 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

void	mat_init(t_matbase *mat)
{
	(void) mat;
}

void	mat_deinit(t_matbase *mat)
{
	(void) mat;
}

// function to compute the color of the material
void	compute_color(t_objbase *p_obj, t_lightbase *p_light, t_objbase *closet_obj, t_scene *scn)
{
	(void) p_obj;
	(void) p_light;
	(void) closet_obj;
	(void) scn;
}

void	compute_diffuse_color(t_objbase *p_obj, t_lightbase *p_light, t_objbase *closet_obj, t_scene *scn)
{
	(void) p_obj;
	(void) p_light;
	(void) closet_obj;
	(void) scn;
}
