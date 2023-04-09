/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:18:28 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/28 21:59:32 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_util.h"

/// @brief Random Floating value under min and max criteria
/// @param min Minumim boundary
/// @param max Maximum boundary
/// @return
float	nml_rand_interval(float min, float max)
{
	float	d;

	d = (float) rand() / ((float) RAND_MAX + 1);
	return (min + d * (max - min));
}

/// @brief NULL Pointer checker
/// @param ptr pointer
void	np_check(void *ptr)
{
	if (!ptr)
	{
		dprintf(STDERR_FILENO, RED "%s: %d NULL POINTER: %s \n" RESET, \
			__FILE__, __LINE__, (char *) ptr);
		exit(-1);
	}
}

/// @brief Information Log on STDOUT
/// @param f_name filename, e.g. __FILE__
/// @param line line of code, e.g. __LINE__
/// @param msg additional message
void	nml_vlog_info(const char *f_name, unsigned int line, \
	const char *msg)
{
	if (DEBUG_TRUE)
	{
		dprintf(STDOUT_FILENO, "[%s:%d] [%s] %s\n", f_name, line, "INFO", msg);
	}
}

/// @brief Error Log on STDERROR
/// @param f_name filename, e.g. __FILE__
/// @param line line of code, e.g. __LINE__
/// @param msg additional message
void	nml_vlog_error(const char *f_name, unsigned int line, \
	const char *msg)
{
	if (DEBUG_TRUE)
	{
		dprintf(STDERR_FILENO, "[%s:%d] [%s] %s\n", f_name, line, "INFO", msg);
	}
}
