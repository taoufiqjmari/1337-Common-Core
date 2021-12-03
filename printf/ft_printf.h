/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 14:53:29 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 21:15:51 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_vars
{
	va_list		ap;
	char		*str;
	char		specifier;
	int			width;
	int			minus;
	int			zero;
	int			precision;
	int			precision_value;
	int			spaces;
	int			zero_adfix;
	int			ret;
}				t_vars;
t_vars			g_vars;

int				ft_printf(const char *format, ...);
int				ft_parameters(void);
void			ft_width(void);
void			ft_precision(void);
void			ft_character(void);
void			ft_string(char *string);
void			ft_pointer(unsigned long pointer);
void			ft_integer(int num);
void			ft_unsigned_int(int num);
void			ft_hexadecimal(unsigned int num);
void			ft_percent(void);
void			ft_spaces(void);
void			ft_zeros(void);
void			ft_zeros_adfix(void);
int				ft_len(long num);
size_t			ft_strlen(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
void			ft_strrev(char **str);
void			ft_putchar(char c);
void			ft_putstr(char *s);
void			ft_putnbr(int c);
void			ft_putnbr_uint(unsigned int num);
void			itox(unsigned int num, char **str);
void			itox_lower(unsigned int num, char **str);
void			itox_upper(unsigned int num, char **str);
void			itox_l_uint(unsigned long num, char **str);

#endif
