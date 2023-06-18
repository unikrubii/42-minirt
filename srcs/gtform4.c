/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtform4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:31:25 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/17 22:11:33 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtform.h"

// Function to return the transform metrices
t_nml_mat	*gt_get_fwd(t_gtform *form)
{
	return (form->fwdtfm);
}

t_nml_mat	*gt_get_bwd(t_gtform *form)
{
	return (form->bwdtfm);
}

/// @brief check matrix dimension equality
/// @param mat
/// @param size
/// @return
int	mateqdim_num(t_nml_mat *mat, unsigned int size)
{
	t_nml_mat	*tmp;
	int			isfour;

	isfour = 0;
	tmp = nml_mat_sqr(size);
	isfour = nml_mat_eqdim(mat, tmp);
	free(tmp);
	return (isfour);
}

void	gt_deinit_mode(t_gtform *form, int mode)
{
	if (mode)
	{
		if (form->fwd)
		{
			nml_mat_free(form->fwd);
			form->fwd = NULL;
		}
		if (form->bwd)
		{
			nml_mat_free(form->bwd);
		}
	}
	if (form->fwdtfm)
	{
		nml_mat_free(form->fwdtfm);
	}
	if (form->bwdtfm)
	{
		nml_mat_free(form->bwdtfm);
	}
	free(form);
}
