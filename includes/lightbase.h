/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightbase.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:38:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/13 11:49:54 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTBASE_H
# define LIGHTBASE_H

# include "nml_matrix.h"
# include "objectbase.h"
# include "ray.h"

enum e_lighttype {
	PNT = 1
};

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
}	t_lightbase;

void	light_init(t_lightbase *light, int type);
void	light_deinit(t_lightbase *light);
int		light_comp_illum(t_lightbase *light, t_nml_mat *intpoint, \
		t_nml_mat *lc_normal, t_objbase *obj, \
		t_objbase *cur_obj, t_nml_mat *color, \
		float *intensity);

void	p_light_init(t_lightbase *light);
void	p_light_deinit(t_lightbase *light);
int		p_light_comp_illum(t_lightbase *light, \
		t_nml_mat *intpoint, t_nml_mat *lc_normal, \
		t_objbase *obj, t_objbase *cur_obj, \
		t_nml_mat *color, float *intensity);

t_lightbase	*lightlst_last(t_lightbase *lst);
void		lightlst_add_back(t_lightbase **lst, t_lightbase *new);
t_lightbase	*lightlst_new(int type);
void		lightlst_clear(t_lightbase **lst);
void		lightlst_print(t_lightbase *lst);

#endif
