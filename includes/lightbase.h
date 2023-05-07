/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightbase.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:38:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/07 20:45:04 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTBASE_H
# define LIGHTBASE_H

# include "nml_matrix.h"
# include "objectbase.h"
# include "ray.h"

typedef struct s_lightbase
{
	int					type;
	t_nml_mat			*v_color;
	t_nml_mat			*v_location;
	float				intensity;
	struct s_lightbase	*next;

	void				(*obj_init)(struct s_lightbase *);
	void				(*obj_deinit)(struct s_lightbase *);
	int					(*obj_comp_illum)(t_nml_mat *intpoint, \
		t_nml_mat *lc_normal, t_objbase *obj, \
		t_objbase *cur_obj, t_nml_mat *color, \
		t_nml_mat *intensity);
}	t_lightbase;

#endif
