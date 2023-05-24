#ifndef READMAP_H
# define READMAP_H

# include "libft.h"
# include "get_next_line.h"

int		get_row(char *path);
int		read_map(int argc, char **argv, t_handle *handy);
char	**get_map(char *path, int row_count);

#endif
