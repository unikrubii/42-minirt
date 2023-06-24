/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_base.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:08:35 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 05:11:43 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BASE_H
# define T_BASE_H

# include "nml_matrix.h"
# include "scene.h"

/// @brief ENUM Light type
/// @note 1, PNT - Point Light
enum e_lighttype {
	PNT = 1
};

/// @brief ENUM Material type
/// @note 1, SIM - Simple Material
enum e_material {
	SIM = 1
};

/// @brief ENUM Object type
/// @note 1, SPH - Sphere
/// @note 2, PLN - Plane
/// @note 3, CYL - Cylinder
/// @note 4, CON - Cone
/// @note 5, HYB - Hyperboloid
/// @note 6, PLB - Paraboloid
enum e_objtype {
	SPH = 1,
	PLN = 2,
	CYL = 3,
	CON = 4,
	HYB = 5,
	PLB = 6
};

/// @brief ENUM Keyboard
enum e_key {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_F = 3,
	KEY_Z = 6,
	KEY_C = 8,
	KEY_R = 15,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_SQBO = 30,
	KEY_O = 31,
	KEY_I = 34,
	KEY_SQBC = 33,
	KEY_P = 35,
	KEY_QUOTE = 39,
	KEY_SEMI = 41,
	KEY_SPACE = 49,
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126,
};

// Material Base Class
typedef struct s_matbase
{
	int					type;
	t_nml_mat			*v_base_color;
	float				reflectivity;
	float				shiness;
	void				(*mat_init)(struct s_matbase *);
	void				(*mat_deinit)(struct s_matbase *);
	void				(*mat_comp_color)(struct s_matbase *, t_scene *scn);
}	t_matbase;

typedef struct s_gtform_calc
{
	t_nml_mat		*transm;
	t_nml_mat		*rotmx;
	t_nml_mat		*rotmy;
	t_nml_mat		*rotmz;
	t_nml_mat		*sclm;
	t_nml_mat		*dot_tmp1;
	t_nml_mat		*dot_tmp2;
	t_nml_mat_lup	*lup;
}	t_gtform_calc;

/// @brief Geometric Transformation Class
typedef struct s_gtform
{
	t_nml_mat		*fwd;
	t_nml_mat		*bwd;
	t_nml_mat		*fwdtfm;
	t_nml_mat		*bwdtfm;

	void			(*gt_form_init)(struct s_gtform *gt_form, \
		t_nml_mat *fwd, t_nml_mat *bwd);
	void			(*gt_form_deinit)(struct s_gtform *gt_form);
	void			(*gt_set_trans)(t_nml_mat *trans, t_nml_mat *rot, \
		t_nml_mat *scale);

	t_nml_mat		*(*gt_get_fwd)(struct s_gtform *gt_form);
	t_nml_mat		*(*gt_get_bwd)(struct s_gtform *gt_form);
	t_ray			*(*ray_apply)(struct s_gtform *gt_form, t_ray *ray, \
		int dir);
	t_nml_mat		*(*gt_apply)(struct s_gtform *gt_form, t_nml_mat *v_inp, \
		int dir);

}	t_gtform;

/// @brief Object Base Class
typedef struct s_objbase
{
	int					type;
	int					id;
	t_nml_mat			*v_base_color;
	t_gtform			*transmat;
	t_matbase			*material;
	int					has_material;
	float				up_x;
	float				up_y;
	float				up_z;
	struct s_objbase	*next;

	void				(*obj_init)(struct s_objbase *);
	void				(*obj_deinit)(struct s_objbase *);
	int					(*obj_test_intersect)(t_ray *ray, \
			t_nml_mat *int_point, t_nml_mat *lc_normal, t_nml_mat *lc_color);
	int					(*obj_test_inter_scn)(struct s_objbase *, t_scene *scn);
	int					(*obj_close_enough)(float f1, float f2);
	void				(*obj_set_trans_mat)(t_gtform *form, \
			t_gtform *transmat);
	int					(*obj_assign_material)(struct s_objbase *, t_matbase *);
}	t_objbase;

/// @brief Light Object Base
typedef struct s_lightbase
{
	int					type;
	t_nml_mat			*v_color;
	t_nml_mat			*v_location;
	float				intensity;
	struct s_lightbase	*next;

	void				(*light_init)(struct s_lightbase *light);
	void				(*light_deinit)(struct s_lightbase *light);
	int					(*light_comp_illum)(struct s_lightbase *light,
			t_nml_mat *intpoint, t_nml_mat *lc_normal, \
			t_objbase *obj, t_objbase *cur_obj, \
			t_nml_mat *color, float *intensity);
	int					(*light_comp_illum_scn)(struct s_lightbase *light,
			t_objbase *obj, t_objbase *cur_obj, t_scene *scn);
}	t_lightbase;

/// @brief For intersect calculation purpose
typedef struct s_inter_calc
{
	t_nml_mat	*vhat;
	t_nml_mat	*vtmp;
	float		a;
	float		b;
	float		c;
	float		inter_test;
	float		num_sqrt;
	float		t1;
	float		t2;
	float		tt[4];
	int			t1_valid;
	int			t2_valid;
	int			t3_valid;
	int			t4_valid;
	int			min_i;
	float		min_t;
	t_nml_mat	*poi[4];
	t_ray		*bck_ray;
	t_nml_mat	*v_poi;
	t_nml_mat	*v_obj_org;
	t_nml_mat	*v_obj_norg;
	t_nml_mat	*k;
	float		t;
	float		u;
	float		v;
	t_nml_mat	*v_obj_norm;
	t_nml_mat	*v_obj_gorg;
	t_nml_mat	*valid_poi;
	t_nml_mat	*org_normal;
	t_nml_mat	*local_origin;
	t_nml_mat	*global_origin;
	float		tx;
	float		ty;
	float		tz;
}	t_inter_calc;

/// @brief Object Attributes
typedef struct s_fattr
{
	t_nml_mat	*v_tr;
	t_nml_mat	*v_rot;
	t_nml_mat	*v_scl;
	t_nml_mat	*v_color;
	t_nml_mat	*up_v;
	t_matbase	*mat;
}	t_fattr;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_draw
{
	int		begin_x;
	int		begin_y;
	int		end_x;
	int		end_y;
	int		color;
}	t_draw;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	img;
}	t_vars;

typedef struct s_mouse
{
	int		is_pressed;
	int		pos_x;
	int		pos_y;
}	t_mouse;

typedef struct s_handle
{
	t_vars		data;
	t_draw		draw;
	t_mouse		mouse;
	t_camera	*camera;
	t_objbase	*objects;
	t_lightbase	*lights;
	int			to_render;
	float		max_red;
	float		max_green;
	float		max_blue;
	float		maxall;
	t_nml_mat	**vv_color;
	int			max_rfl_ray;
	int			rfl_ray_cnt;
	float		amb_factor;
	float		amb_red;
	float		amb_green;
	float		amb_blue;
}	t_handle;

#endif
