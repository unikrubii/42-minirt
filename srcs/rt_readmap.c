/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_readmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:08:06 by sthitiku          #+#    #+#             */
/*   Updated: 2023/06/24 21:22:19 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_row(char *path)
{
	char	*line;
	int		row_count;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		dprintf(2, "Error\nCan't open file\n");
		exit (1);
	}
	line = get_next_line(fd);
	row_count = 0;
	while (line)
	{
		row_count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (row_count);
}

void	check_path(char *path)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(path);
	if (len < 3)
	{
		dprintf(2, "Error\nWrong file name\n");
		exit (1);
	}
	while (path[i])
	{
		if (path[i] == '.' && path[i + 1] == 'r' && path[i + 2] == 't' && \
			path[i + 3] == '\0')
			return ;
		i++;
	}
	dprintf(2, "Error\nWrong file name\n");
	exit (1);
}

char **get_map(char *path, int row_count)
{
	char	*line;
	char	**map;
	int		i;
	int		fd;

	check_path(path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		dprintf(2, "Error\nCan't open file\n");
		return (0);
	}
	map = (char **)malloc(sizeof(char *) * (row_count + 1));
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (line[0] != '\n')
			map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void	*object_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = malloc(size + 1);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

t_matbase	*set_material(int type, t_nml_mat *color, float rfl, float shn)
{
	t_matbase	*mat;

	mat = malloc(sizeof(t_matbase));
	mat_init(mat);
	mat->type = type;
	set_vect_from_vect(color, mat->v_base_color);
	mat->reflectivity = rfl;
	mat->shiness = shn;
	return (mat);
}


void	construct_light(char **light_data, t_handle *handy, int id)
{
	(void)id;
	lightlst_add_back(&handy->lights, lightlst_new(PNT, light_data));
}

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
			set_vect(att.v_color, rt_atof(d[0]) / 255.0, rt_atof(d[1]) / 255.0, rt_atof(d[2]) / 255.0);
		free_arr(d);
		i++;
	}
	set_vect(att.v_rot, 0.0, 0.0, 0.0);
	att.mat = set_material(SIM, att.v_color, 0.0, 10.0);
	objlst_add_back(&handy->objects, objlst_new(SPH, &att, id));
}

void	construct_plane(char **pl_data, t_handle *handy, int id)
{
	t_fattr att;
	char	**d;
	int		i;

	att.v_tr = new_vector();
	att.v_rot = new_vector();
	att.v_scl = new_vector();
	att.v_color = new_vector();
	att.up_v = new_vector();
	i = 1;
	while (pl_data[i])
	{
		d = ft_split(pl_data[i], ',');
		if (i == 1)
			set_vect(att.v_tr, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
		else if (i == 2)
			set_vect(att.up_v, rt_atof(d[0]), rt_atof(d[2]), -rt_atof(d[1]));
		else if (i == 3)
			set_vect(att.v_color, rt_atof(d[0]) / 255.0, rt_atof(d[1]) / 255.0, rt_atof(d[2]) / 255.0);
		free_arr(d);
		i++;
	}
	set_vect(att.v_rot, 0.0, 0.0, 0.0);
	set_vect(att.v_scl, 100, 100, 100);
	att.mat = set_material(SIM, att.v_color, 0.5, 10.0);
	// att.mat = set_material(SIM, att.v_color, time(NULL) % 10 / 10.0, time(NULL) % 100 / 10.0);
	objlst_add_back(&handy->objects, objlst_new(PLN, &att, id));
}

void	construct_camera(char **c_data, t_handle *handy)
{
	// cam is malloced and has not yet to be freed
	printf("CAM!");
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

void	set_scl_vect(t_nml_mat **v_scl, char *d, char *h)
{
	float	diameter;
	float	height;

	diameter = rt_atof(d);
	height = rt_atof(h);
	if (diameter < 0 || height < 0)
	{
		dprintf(2, "Error\nWrong cylinder scale\n");
		exit (1);
	}
	set_vect(*v_scl, diameter, diameter, height);
}

void	construct_cylinder(char **cy_data, t_handle *handy, int id)
{
	printf("Cylinder!\n");
	t_fattr	att;
	char	**d;
	int		i;

	att.v_tr = new_vector();
	att.up_v = new_vector();
	att.v_scl = new_vector();
	att.v_color = new_vector();
	att.v_rot = new_vector();
	i = 1;
	while (cy_data[i])
	{
		d = ft_split(cy_data[i], ',');
		if (i == 1)
			set_vect(att.v_tr, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
		else if (i == 2)
			set_vect(att.up_v, rt_atof(d[0]), rt_atof(d[2]), -rt_atof(d[1]));
		else if (i == 5)
			set_vect(att.v_color, rt_atof(d[0]) / 255.0, rt_atof(d[1]) / 255.0, rt_atof(d[2]) / 255.0);
		else if (i == 6)
			set_vect(att.v_rot, rt_atof(d[0]) * ONE_DEG, \
				rt_atof(d[1]) * ONE_DEG, rt_atof(d[2]) * ONE_DEG);
		free_arr(d);
		i++;
	}
	set_vect(att.v_scl, rt_atof(cy_data[3]), rt_atof(cy_data[3]), rt_atof(cy_data[4]));
	att.mat = set_material(SIM, att.v_color, 0.0, 10.0);
	objlst_add_back(&handy->objects, objlst_new(CYL, &att, id));
}

void	construct_cone(char **cone_data, t_handle *handy, int id)
{
	t_fattr	att;
	char	**d;
	int		i;

	att.v_tr = new_vector();
	att.up_v = new_vector();
	att.v_scl = new_vector();
	att.v_color = new_vector();
	att.v_rot = new_vector();
	i = 1;
	while (cone_data[i])
	{
		d = ft_split(cone_data[i], ',');
		if (i == 1)
			set_vect(att.v_tr, rt_atof(d[0]), rt_atof(d[1]), rt_atof(d[2]));
		else if (i == 2)
			set_vect(att.up_v, rt_atof(d[0]), rt_atof(d[2]), -rt_atof(d[1]));
		else if (i == 5)
			set_vect(att.v_color, rt_atof(d[0]) / 255.0, rt_atof(d[1]) / 255.0, rt_atof(d[2]) / 255.0);
		else if (i == 6)
			set_vect(att.v_rot, rt_atof(d[0]) * ONE_DEG, \
				rt_atof(d[1]) * ONE_DEG, rt_atof(d[2]) * ONE_DEG);
		free_arr(d);
		i++;
	}
	set_vect(att.v_scl, rt_atof(cone_data[3]), rt_atof(cone_data[3]), rt_atof(cone_data[4]));
	att.mat = set_material(SIM, att.v_color, 0.0, 20.0);
	// att.mat = set_material(SIM, att.v_color, time(NULL) % 10 / 10.0, time(NULL) % 100 / 10.0);
	objlst_add_back(&handy->objects, objlst_new(CON, &att, id));
}

void	get_obj_type(char *map, t_handle *handy, int id)
{
	char	**map_arr;
	int		size;

	map_arr = ft_split(map, ' ');
	size = array_size(map_arr);
	if (!ft_strncmp(map_arr[0], "A\0", 2) && size == 3)
		printf("Ambient light\n");
	else if (!ft_strncmp(map_arr[0], "C\0", 2) && size == 4)
		construct_camera(map_arr, handy);
	else if (!ft_strncmp(map_arr[0], "L\0", 2) && size == 4)
		construct_light(map_arr, handy, id);
	else if (!ft_strncmp(map_arr[0], "sp\0", 3) && size == 4)
		construct_sphere(map_arr, handy, id);
	else if (!ft_strncmp(map_arr[0], "pl\0", 3) && size == 4)
		construct_plane(map_arr, handy, id);
	else if (!ft_strncmp(map_arr[0], "cy\0", 3) && size == 7)
		construct_cylinder(map_arr, handy, id);
	else if (!ft_strncmp(map_arr[0], "cn\0", 3) && size == 7)
		construct_cone(map_arr, handy, id);
	else
		printf("Error\nWrong object type\n");
	free_arr(map_arr);
}

int read_map(int argc, char **argv, t_handle *handy)
{
	(void)handy;
	char **map;
	int i;

	if (argc != 2)
	{
		dprintf(2, "Error\nWrong number of arguments\n");
		exit (0);
	}
	map = get_map(argv[1], get_row(argv[1]));
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		get_obj_type(map[i], handy, i + 1);
		printf("===================\n");
		i++;
	}
	free_arr(map);
	return (0);
}
