/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:49:04 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/11 20:30:04 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdbool.h>

# define BIGNUMDIGITS 200

typedef	char	t_bignum[BIGNUMDIGITS];

typedef struct	s_data
{
	bool		alternate_form;
	bool		zero_padding;
	bool		left_ajusted;
	bool		space_before_positive_num;
	bool		show_plus_sign;
	int			field_width;
	int			precision;
	int			len_mod;
	char		prefix[3];
	int			prefix_len;
	char		base[20];
	int			base_len;
	char		converted[BIGNUMDIGITS];
	int			conv_len;
	t_bignum	big;
	int			*print_count;
	int			fd;
}				t_data;

int				ft_dprintf(int fd, const char *format, ...);
int				ft_printf(const char *format, ...);
void			bignum_from_int(t_bignum big, unsigned int n);
void			bignum_add(t_bignum dst, t_bignum src);
void			bignum_mul(t_bignum big, int n);
void			bignum_rshift(t_bignum big, unsigned int shift);
void			bignum_pow(t_bignum big, unsigned int x, unsigned int y);
int				ft_wcharlen(wchar_t c);
void			ft_putwchar_fd(wchar_t c, int fd);
void			parse_color(char **format, int *print_count, int fd);
void			parse_flags(char **s, t_data *d);
void			parse_field_width(char **s, t_data *d, va_list valist);
void			parse_precision(char **s, t_data *d, va_list valist);
void			parse_len_modifier(char **s, t_data *d);
void			diuoxb_padding_and_print(t_data *d);
void			get_sign(bool is_neg, t_data *d);
void			di_conv(intmax_t n, t_data *d);
void			uoxb_conv(uintmax_t n, char c, t_data *d);
void			c_conv(char c, t_data *d);
void			wchar_conv(wchar_t c, t_data *d);
void			s_conv(char *s, t_data *d);
void			wstr_conv(wchar_t *s, t_data *d);
void			non_printable_str_conv(char *s, t_data *d);
void			float128_conv(long double f, bool uppercase, t_data *d);
void			print_bits(uintmax_t bits, int shift, t_data *d);
void			print_iso8601_date(int32_t date, t_data *d);
intmax_t		get_signed(t_data *d, va_list valist);
uintmax_t		get_unsigned(t_data *d, va_list valist);
long double		get_float(t_data *d, va_list valist);
void			convert(char **s, t_data *d, va_list valist);

#endif
