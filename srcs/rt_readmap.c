/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_readmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:08:06 by sthitiku          #+#    #+#             */
/*   Updated: 2023/05/27 19:13:49 by sthitiku         ###   ########.fr       */
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
		perror("Error\nCan't open file\n");
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

char **get_map(char *path, int row_count)
{
	char	*line;
	char	**map;
	int		i;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nCan't open file\n");
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

void	construct_light(char **light_data, t_handle *handy)
{
	int	i;

	i = 0;
	lightlst_add_back(&handy->lights, lightlst_new(PNT, light_data));
}

void	get_obj_type(char *map, t_handle *handy)
{
	(void)handy;
	char	**map_arr;
	int		size;

	map_arr = ft_split(map, ' ');
	size = array_size(map_arr);
	if (!ft_strncmp(map_arr[0], "A\0", 2) && size == 3)
		printf("Ambient light\n");
	else if (!ft_strncmp(map_arr[0], "C\0", 2) && size == 4)
		printf("Camera\n");
	else if (!ft_strncmp(map_arr[0], "L\0", 2) && size == 4)
		construct_light(map_arr, handy);
	else if (!ft_strncmp(map_arr[0], "sp\0", 3) && size == 4)
		printf("Sphere\n");
	else if (!ft_strncmp(map_arr[0], "pl\0", 3) && size == 4)
		printf("Plane\n");
	else if (!ft_strncmp(map_arr[0], "cy\0", 3) && size == 6)
		printf("Cylinder\n");
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
		perror("Error\nWrong number of arguments\n");
		exit (0);
	}
	map = get_map(argv[1], get_row(argv[1]));
	i = 0;
	while (map[i])
	{
		printf("%s", map[i]);
		get_obj_type(map[i], handy);
		printf("===================\n");
		i++;
	}
	free_arr(map);
	return (0);
}
