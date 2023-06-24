/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_cyl_cn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:55:54 by sthitiku          #+#    #+#             */
/*   Updated: 2023/06/24 23:59:41 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	cyl_cn_set_loop(char **data, t_fattr *att, int i)
{
	char	**d;

	d = ft_split(data[i], ',');
	if (i == 1)
		set_vect(att->v_tr, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
	else if (i == 2)
		set_vect(att->up_v, rt_atof(d[0]), rt_atof(d[2]), -rt_atof(d[1]));
	else if (i == 5)
		set_vect(att->v_color, rt_atof(d[0]) / 255.0, \
			rt_atof(d[1]) / 255.0, rt_atof(d[2]) / 255.0);
	else if (i == 6)
		set_vect(att->v_rot, rt_atof(d[0]) * ONE_DEG, \
			rt_atof(d[1]) * ONE_DEG, rt_atof(d[2]) * ONE_DEG);
	free_arr(d);
}

void	construct_cylinder(char **cy_data, t_handle *handy, int id)
{
	t_fattr	att;
	int		i;

	att.v_tr = new_vector();
	att.up_v = new_vector();
	att.v_scl = new_vector();
	att.v_color = new_vector();
	att.v_rot = new_vector();
	i = 0;
	while (cy_data[++i])
		cyl_cn_set_loop(cy_data, &att, i);
	set_vect(att.v_scl, rt_atof(cy_data[3]), \
		rt_atof(cy_data[3]), rt_atof(cy_data[4]));
	att.mat = set_material(SIM, att.v_color, 0.0, 10.0);
	objlst_add_back(&handy->objects, objlst_new(CYL, &att, id));
}

void	construct_cone(char **cone_data, t_handle *handy, int id)
{
	t_fattr	att;
	int		i;

	att.v_tr = new_vector();
	att.up_v = new_vector();
	att.v_scl = new_vector();
	att.v_color = new_vector();
	att.v_rot = new_vector();
	i = 0;
	while (cone_data[++i])
	{
		cyl_cn_set_loop(cone_data, &att, i);
	}
	set_vect(att.v_scl, rt_atof(cone_data[3]), \
		rt_atof(cone_data[3]), rt_atof(cone_data[4]));
	att.mat = set_material(SIM, att.v_color, 0.0, 20.0);
	objlst_add_back(&handy->objects, objlst_new(CON, &att, id));
}

	// att.mat = set_material(SIM, att.v_color, time(NULL) % 10 / 10.0, time(NULL) % 100 / 10.0);