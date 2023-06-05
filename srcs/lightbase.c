/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 02:46:43 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/05 23:30:43 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lightbase.h"

void	set_light_color(t_lightbase *light, char *data)
{
	char	**color;

	color = ft_split(data, ',');
	set_vect(light->v_color, rt_atof(color[0]), rt_atof(color[1]), \
		rt_atof(color[2]));
	free_arr(color);
}

void	set_light_coord(t_lightbase *light, char *data)
{
	char	**coord;

	coord = ft_split(data, ',');
	set_vect(light->v_location, rt_atof(coord[0]), rt_atof(coord[1]), \
		rt_atof(coord[2]));
	free_arr(coord);
}

void	light_init(t_lightbase *light, int type, char **l_data)
{
	light->type = type;
	light->v_color = new_vector();
	light->v_location = new_vector();
	set_light_coord(light, l_data[1]);
	set_light_color(light, l_data[3]);
	// set_vect(light->v_location, 5.0, -20.0, -5.0);
	// set_vect(light->v_color, 255.0, 255.0, 255.0);
	light->next = NULL;
	light->intensity = rt_atof(l_data[2]);
	// light->intensity = 0.0;
	if (type == PNT)
	{
		light->light_init = p_light_init;
		light->light_comp_illum_scn = p_light_comp_illum_scn;
		light->light_init(light);
	}
}

void	light_deinit(t_lightbase *light)
{
	(void) light;
}
