/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightbase.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 20:38:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 05:17:50 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTBASE_H
# define LIGHTBASE_H

# include "nml_matrix.h"
# include "objectbase.h"
# include "ray.h"
# include "scene.h"
# include "t_base.h"

void		light_init(t_lightbase *light, int type, char **light_data);
void		light_deinit(t_lightbase *light);

void		p_light_init(t_lightbase *light);
void		p_light_deinit(t_lightbase *light);
int			p_light_comp_illum_scn(t_lightbase *light, \
			t_objbase *obj, t_objbase *cur_obj, t_scene *scn);
int			p_light_comp_illum_scn_close(t_lightbase *light, \
			t_objbase *obj, t_objbase *cur_obj, t_scene *scn);

t_lightbase	*lightlst_last(t_lightbase *lst);
void		lightlst_add_back(t_lightbase **lst, t_lightbase *new);
t_lightbase	*lightlst_new(int type, char **light_data);
void		lightlst_clear(t_lightbase **lst);
void		lightlst_print(t_lightbase *lst);

#endif
