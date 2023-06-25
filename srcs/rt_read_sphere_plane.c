/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_sphere_plane.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:55:54 by sthitiku          #+#    #+#             */
/*   Updated: 2023/06/25 11:34:43 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	construct_sphere(char **sp_data, t_handle *handy, int id)
{
	t_fattr	att;
	char	**d;
	int		i;

	att.v_tr = new_vector();
	att.v_rot = new_vector();
	att.v_scl = new_vector();
	att.v_color = new_vector();
	i = 1;
	while (sp_data[i])
	{
		d = ft_split(sp_data[i], ',');
		if (i == 1)
			set_vect(att.v_tr, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
		else if (i == 2)
			set_vect(att.v_scl, rt_atof(d[0]), rt_atof(d[0]), rt_atof(d[0]));
		else if (i == 3)
			set_vect(att.v_color, rt_atof(d[0]) / 255.0, \
				rt_atof(d[1]) / 255.0, rt_atof(d[2]) / 255.0);
		free_arr(d);
		i++;
	}
	set_vect(att.v_rot, 0.0, 0.0, 0.0);
	att.mat = set_material(SIM, att.v_color, 0.0, 10.0);
	objlst_add_back(&handy->objects, objlst_new(SPH, &att, id));
}

void	plane_set_loop(char **pl_data, t_fattr *att, int i)
{
	char	**d;

	d = ft_split(pl_data[i], ',');
	if (i == 1)
		set_vect(att->v_tr, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
	else if (i == 2)
		set_vect(att->up_v, rt_atof(d[0]), rt_atof(d[2]), -rt_atof(d[1]));
	else if (i == 3)
		set_vect(att->v_color, rt_atof(d[0]) / 255.0, \
			rt_atof(d[1]) / 255.0, rt_atof(d[2]) / 255.0);
	free_arr(d);
}

void	construct_plane(char **pl_data, t_handle *handy, int id)
{
	t_fattr	att;
	int		i;

	att.v_tr = new_vector();
	att.v_rot = new_vector();
	att.v_scl = new_vector();
	att.v_color = new_vector();
	att.up_v = new_vector();
	i = 0;
	while (pl_data[++i])
		plane_set_loop(pl_data, &att, i);
	set_vect(att.v_rot, 0.0, 0.0, 0.0);
	set_vect(att.v_scl, 100, 100, 100);
	att.mat = set_material(SIM, att.v_color, 0.5, 10.0);
	objlst_add_back(&handy->objects, objlst_new(PLN, &att, id));
}

// For set random material
// att.mat = set_material(SIM, att.v_color, time(NULL) % 10 / 
	// 10.0, time(NULL) % 100 / 10.0);
