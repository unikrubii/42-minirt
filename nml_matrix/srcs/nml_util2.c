/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 19:58:40 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/27 12:52:03 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nml_util.h"

/// @brief log message with file and line of em
/// @param f_name
/// @param line
/// @param msg
void	nml_flog(const char *f_name, unsigned int line, const char *msg)
{
	if (DEBUG_TRUE)
	{
		nml_vlog_info(f_name, line, msg);
	}
}

/// @brief info message with file and line of em
/// @param f_name
/// @param line
/// @param msg
void	nml_finfo(const char *f_name, unsigned int line, const char *msg)
{
	if (DEBUG_TRUE)
	{
		nml_vlog_info(f_name, line, msg);
	}
}

/// @brief error message with file and line of em
/// @param f_name
/// @param line
/// @param msg
void	nml_ferror(const char *f_name, unsigned int line, const char *msg)
{
	if (DEBUG_TRUE)
	{
		nml_vlog_error(f_name, line, msg);
	}
}

/// @brief error message with file and line of em
/// @param f_name
/// @param line
/// @param msg
void	nml_error(const char *f_name, unsigned int line, const char *msg)
{
	if (DEBUG_TRUE)
		nml_vlog_error(f_name, line, msg);
}
