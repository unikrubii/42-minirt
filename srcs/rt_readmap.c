/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_readmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:08:06 by sthitiku          #+#    #+#             */
/*   Updated: 2023/06/24 23:18:12 by sthitiku         ###   ########.fr       */
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

char	**get_map(char *path, int row_count)
{
	char	*line;
	char	**map;
	int		i;
	int		fd;

	check_path(path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit(printf("Error\nCan't open file\n"));
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

int	read_map(int argc, char **argv, t_handle *handy)
{
	char	**map;
	int		i;

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
