/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 02:46:43 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/13 11:51:22 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lightbase.h"

void	light_init(t_lightbase *light, int type)
{
	light->type = type;
	light->v_color = new_vector();
	light->v_location = new_vector();
	light->next = NULL;
	light->intensity = 0.0;
	if (type == PNT)
	{
		light->light_init = p_light_init;
		light->light_comp_illum = p_light_comp_illum;
		light->light_init(light);
	}
}

void	light_deinit(t_lightbase *light)
{
	(void) light;
}

int	light_comp_illum(t_lightbase *light, t_nml_mat *intpoint, \
	t_nml_mat *lc_normal, t_objbase *obj, \
	t_objbase *cur_obj, t_nml_mat *color, \
	float *intensity)
{
	(void) intpoint;
	(void) lc_normal;
	(void) obj;
	(void) cur_obj;
	(void) color;
	(void) intensity;
	(void) light;
	return (0);
}
