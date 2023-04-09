/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nml_util.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:43:00 by nnakarac          #+#    #+#             */
/*   Updated: 2023/03/26 21:42:15 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NML_UTIL_H
# define NML_UTIL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <time.h>
# include <err.h>
# include <fcntl.h>
# include "nml_util.h"
# include "libft.h"
# include "../../libft/includes/libft.h"

// Enable this to allow debugging messages
# define DEBUG_TRUE 1
# define BUFFER_SIZE 4096

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define YELLOW "\033[0;33m"
# define RESET "\033[0m"

float	nml_rand_interval(float min, float max);

void	np_check(void *ptr);

// void nml_log(FILE *stream, const char *file_name,
//   unsigned int line, const char *format, ...);

// void	nml_vlog(FILE* stream, const char *file_name,
// unsigned int line, const char *format, va_list argp);

void	nml_vlog_info(const char *f_name, unsigned int line, \
	const char *msg);
void	nml_vlog_error(const char *f_name, unsigned int line, \
	const char *msg);

void	nml_flog(const char *f_name, unsigned int line, const char *msg);
void	nml_finfo(const char *f_name, unsigned int line, const char *msg);
void	nml_ferror(const char *f_name, unsigned int line, const char *msg);
void	nml_error(const char *f_name, unsigned int line, const char *msg);

#endif
