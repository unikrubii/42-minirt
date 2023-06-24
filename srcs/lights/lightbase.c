/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 02:46:43 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/24 23:45:39 by nnakarac         ###   ########.fr       */
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
	light->next = NULL;
	light->intensity = rt_atof(l_data[2]);
	if (type == PNT)
	{
		light->light_init = p_light_init;
		light->light_comp_illum_scn = p_light_comp_illum_scn_close;
		light->light_init(light);
	}
}

void	light_deinit(t_lightbase *light)
{
	(void) light;
	nml_mat_free(light->v_color);
	nml_mat_free(light->v_location);
}
