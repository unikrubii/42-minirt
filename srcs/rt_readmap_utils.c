/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_readmap_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 23:09:20 by sthitiku          #+#    #+#             */
/*   Updated: 2023/06/24 23:18:55 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matbase	*set_material(int type, t_nml_mat *color, float rfl, float shn)
{
	t_matbase	*mat;

	mat = malloc(sizeof(t_matbase));
	mat_init(mat);
	mat->type = type;
	set_vect_from_vect(color, mat->v_base_color);
	mat->reflectivity = rfl;
	mat->shiness = shn;
	return (mat);
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

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
