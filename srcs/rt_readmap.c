#include "readmap.h"

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

int read_map(int argc, char **argv)
{
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
		printf("%s", map[i++]);
	return (0);
}
