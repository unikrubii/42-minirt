/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightlist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 03:02:16 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/13 11:51:54 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "lightbase.h"

t_lightbase	*lightlst_last(t_lightbase *lst)
{
	t_lightbase	*p_lst;

	p_lst = lst;
	if (!p_lst)
		return (p_lst);
	while (p_lst->next)
	{
		p_lst = p_lst->next;
	}
	return (p_lst);
}

void	lightlst_add_back(t_lightbase **lst, t_lightbase *new)
{
	t_lightbase	*p_lst;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	p_lst = lightlst_last(*lst);
	while (p_lst->next != NULL)
		p_lst = p_lst->next;
	p_lst->next = new;
}

t_lightbase	*lightlst_new(int type)
{
	t_lightbase	*new;

	new = malloc(sizeof(t_lightbase));
	if (!new)
		return (NULL);
	light_init(new, type);
	new->next = NULL;
	return (new);
}

void	lightlst_clear(t_lightbase **lst)
{
	t_lightbase	*p_lst;
	t_lightbase	*tmp;

	p_lst = *lst;
	while (p_lst != NULL)
	{
		tmp = p_lst->next;
		light_deinit(p_lst);
		free(p_lst);
		p_lst = tmp;
	}
	*lst = NULL;
}

void	lightlst_print(t_lightbase *lst)
{
	t_lightbase	*p_lst;

	p_lst = lst;
	while (p_lst != NULL)
	{
		printf("type: %d\n", p_lst->type);
		p_lst = p_lst->next;
	}
}
