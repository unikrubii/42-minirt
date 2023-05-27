/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 02:46:43 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/27 12:42:51 by nnakarac         ###   ########.fr       */
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
		// light->light_comp_illum_scn = p_light_comp_illum_scn;
		light->light_comp_illum_scn = p_light_comp_illum_scn_close;
		light->light_init(light);
	}
}

void	light_deinit(t_lightbase *light)
{
	(void) light;
}
