/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 17:55:47 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 17:51:34 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <wchar.h>
# include "libft.h"

#ifdef _WIN32
    #include <stdio.h>
    #define FPURGE(x) fpurge(x)
#elif __APPLE__
   #include "TargetConditionals.h"
   #if TARGET_OS_MAC
        #include <stdio.h>
        #define FPURGE(x) fpurge(x)
   #endif
#elif __linux__
    #include <stdio_ext.h>
    #define FPURGE(x) __fpurge(x)
#endif

typedef struct	s_flag
{
	int		hyphen;
	int		plus;
	int		hash;
	int		zero;
	int		blank;
}				t_flag;

/*
** conv_id = the index of the argument(conversion) type
** conv_type = the argument type (sSpdDioOuUxXcCeEfFgGaAn%)
** field = the minimum field size
** period = dot '.'
** preci = lol ?
** arg_int/arg_uint = the current (va_arg)/argument
** base = (8,10,16) see get_base()
** i = the index of the *format string
** con_res = the result of any conversion
*/

typedef struct	s_format_id
{
	int				conv_id;
	char			conv_type;
	char			conv_type_origin;
	int				modifier[6];
	size_t			field;
	int				period;
	int				preci;
	intmax_t		arg_int;
	uintmax_t		arg_uint;
	unsigned int	base;
	size_t			i;
	char			*conv_res;
	int				nbchar;
	int				invalid;
	int				error;
	t_flag			*flag;
}				t_f_id;

int				(*g_conv_list[15])(const char*, va_list, t_f_id*);
int				ft_printf(const char *s, ...);

/*
** utils.c
*/

void			get_field_n_preci(const char *format, t_f_id *id);
void			get_flags(const char *format, t_f_id *id);
void			get_modifier(const char *format, t_f_id *id);
int				get_base(char c);
int				tododge(char c);

/*
** wide_utils.c
*/

size_t			my_wcharlen(wchar_t wc);
size_t			my_wstrlen(wchar_t *ws);
int				my_putwchar(wint_t wc);
int				my_putwstr(wchar_t *wstr, size_t len);
size_t			get_wpreci(wchar_t *wstr, int idpreci, size_t preci);

/*
** conv_*.c
*/

int				conv_int(const char *f, va_list ap, t_f_id *id);
int				conv_char(const char *f, va_list ap, t_f_id *id);
int				conv_string(const char *f, va_list ap, t_f_id *id);
int				conv_percent(const char *f, va_list ap, t_f_id *id);

/*
** print.c
*/

size_t			my_strlen (const char *s);
int				write_n(const char c, int len);
int				print(size_t len, t_f_id *id);

/*
** itoa.c
*/

char			*my_itoa(t_f_id *id, char sign);
char			*my_uitoa_base(uintmax_t nb, t_f_id *id, int size);

/*
** init.c
*/

void			get_conv_list(void);
void			init(t_f_id *id);

#endif
