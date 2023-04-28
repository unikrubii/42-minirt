#ifndef MINIRT_H
# define MINIRT_H

# include "nml_matrix.h"
# include "nml_util.h"
# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"

# define PI 3.14159265358979323846
# define EPSILON 0.000001
# define WIDTH 800
# define HEIGHT 600

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct	s_vec {
	float	x;
	float	y;
	float	z;
}				t_vec;

typedef struct s_color {
	float	r;
	float	g;
	float	b;
}				t_color;

typedef struct s_amb {
	float	ratio;
	t_color	color;
}				t_amb;

typedef struct s_cam {
	t_vec	origin;
	t_vec	nml;
	float	fov;
}				t_cam;

typedef struct s_light {
	t_vec	origin;
	float	ratio;
	t_color	color;
}				t_light;

typedef struct s_sphere {
	t_vec	origin;
	float	diameter;
	t_color	color;
}				t_sphere;

typedef struct s_plane {
	t_vec	origin;
	t_vec	nml;
	t_color	color;
}				t_plane;

typedef struct s_cylinder {
	t_vec	origin;
	t_vec	nml;
	float	diameter;
	float	height;
	t_color	color;
}				t_cylinder;

typedef struct s_scene {
	t_amb		*amb;
	t_list		*cam;
	t_list		*light;
	t_list		*sphere;
	t_list		*plane;
	t_list		*cylinder;
}				t_scene;

#endif