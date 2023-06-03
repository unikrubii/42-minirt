/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 19:17:52 by nnakarac          #+#    #+#             */
/*   Updated: 2023/05/27 23:42:12 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	ten_pow(int pow)
{
	float	ret;

	ret = 1.0;
	while (pow > 0)
	{
		ret *= 10.0;
		pow--;
	}
	return (ret);
}

static float	f_resolve(char *str)
{
	char	**f_digit;
	float	ret;

	f_digit = ft_split(str, '.');
	ret = (float)(ft_atoi(f_digit[0]));
	if (f_digit[1])
		ret += (float)(ft_atoi(f_digit[1]) / ten_pow(ft_strlen(f_digit[1])));
	free_arr(f_digit);
	return (ret);
}

float	rt_atof(char *str)
{
	float	sign;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			sign = -1.0;
			i++;
		}
		if (str[i] == '-')
		{
			perror("Invalid input");
			exit (-1);
		}
		if (ft_isdigit(str[i]))
			break ;
	}
	return (f_resolve(&str[i]) * sign);
}
