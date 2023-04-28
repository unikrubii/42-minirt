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
		map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

void init_scene(t_scene *scene)
{
	scene->res = NULL;
	scene->amb = NULL;
	scene->cam = NULL;
	scene->light = NULL;
	scene->obj = NULL;
}

t_amb *set_amb(char *line)
{
	t_amb *amb;

	amb = (t_amb *)malloc(sizeof(t_amb));
	if (!amb)
		return (NULL);
	amb->ratio = ft_atof(line + 2);
	amb->color = set_color(line + 2);
	return (amb);
}

void set_scene(t_scene *scene, char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		if (map[i][0] == 'A')
			scene->amb = set_amb(map[i]);
	}
}

int main(int argc, char **argv)
{
	char **map;
	int i;

	if (argc != 2)
	{
		perror("Error\nWrong number of arguments\n");
		return (0);
	}
	map = get_map(argv[1], get_row(argv[1]));
	i = 0;
	while (map[i])
		printf("%s", map[i++]);
	return (0);
}
