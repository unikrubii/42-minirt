/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objectlist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 00:13:06 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/28 00:12:33 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "objectbase.h"

t_objbase	*objlst_last(t_objbase *lst)
{
	t_objbase	*p_lst;

	p_lst = lst;
	if (!p_lst)
		return (p_lst);
	while (p_lst->next)
	{
		p_lst = p_lst->next;
	}
	return (p_lst);
}

void	objlst_add_back(t_objbase **lst, t_objbase *new)
{
	t_objbase	*p_lst;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p_lst = objlst_last(*lst);
	while (p_lst->next != NULL)
		p_lst = p_lst->next;
	p_lst->next = new;
}

t_objbase	*objlst_new(int type, t_fattr *attr, char **o_data)
{
	t_objbase	*new;

	new = malloc(sizeof(t_objbase));
	if (!new)
		return (NULL);
	obj_init(new, type, attr, o_data);
	new->next = NULL;
	return (new);
}

void	objlst_clear(t_objbase **lst)
{
	t_objbase	*p_lst;
	t_objbase	*tmp;

	p_lst = *lst;
	while (p_lst != NULL)
	{
		tmp = p_lst->next;
		obj_deinit(p_lst);
		free(p_lst);
		p_lst = tmp;
	}
	*lst = NULL;
}

void	objlst_print(t_objbase *lst)
{
	t_objbase	*p_lst;

	p_lst = lst;
	while (p_lst != NULL)
	{
		printf("type: %d\n", p_lst->type);
		p_lst = p_lst->next;
	}
}
