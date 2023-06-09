/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_read_cam_light.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 22:55:54 by sthitiku          #+#    #+#             */
/*   Updated: 2023/06/25 11:42:22 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>

void	construct_ambient(char **map_arr, t_handle *handy)
{
	char	**d;

	handy->amb_factor = rt_atof(map_arr[1]);
	d = ft_split(map_arr[2], ',');
	handy->amb_red = rt_atof(d[0]);
	handy->amb_green = rt_atof(d[1]);
	handy->amb_blue = rt_atof(d[2]);
	free_arr(d);
}

void	construct_light(char **light_data, t_handle *handy, int id)
{
	(void)id;
	lightlst_add_back(&handy->lights, lightlst_new(PNT, light_data));
}

void	construct_camera(char **c_data, t_handle *handy)
{
	t_camera	*cam;
	char		**d;
	int			i;

	cam = (t_camera *)malloc(sizeof(t_camera));
	camera_init(cam);
	i = 1;
	while (c_data[i])
	{
		d = ft_split(c_data[i], ',');
		if (i == 1)
			cam_set_pos(cam, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
		else if (i == 2)
			cam_set_up(cam, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
		else if (i == 3)
			cam_set_hor_size(cam, rt_atof(d[0]) / (float)180);
		free_arr(d);
		i++;
	}
	cam_set_lookat(cam, 0.0, 0.0, 0.0);
	cam_set_length(cam, 1.0);
	cam_set_aspr(cam, 4.0 / 3.0);
	update_cam_geomet(cam);
	handy->camera = cam;
}

//	att.mat = set_material(SIM, att.v_color, 
//		time(NULL) % 10 / 10.0, time(NULL) % 100 / 10.0);