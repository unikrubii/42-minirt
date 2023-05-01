#ifndef READMAP_H
# define READMAP_H

# include "libft.h"
# include "get_next_line.h"

typedef struct object_scene

int		get_row(char *path);
char	**get_map(char *path, int row_count);

#endif
