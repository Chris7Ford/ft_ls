/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chford <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 18:10:51 by chford            #+#    #+#             */
/*   Updated: 2019/05/16 12:48:31 by chford           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define ALTERNATE		1
# define ZERO			2
# define SPACE			4
# define MINUS			8
# define PLUS			16
# define HH				1
# define H				2
# define L				4
# define LL				8
# define CL				16
# define F				32
# define C				1
# define S				2
# define P				4
# define D				8
# define O				16

/*
** F is already defined at 32
*/

# define U				64
# define X				128
# define CX				256
# define PERCENT		512
# define D_MANTISSA_LEN 52
# define FALSE			0

typedef struct s_format			t_format;
struct							s_format
{
	void						*value;
	int							precision;
	int							width;
	unsigned int				length : 6;
	unsigned int				flags : 5;
	unsigned int				spec : 10;
	int							fd;
};

typedef union u_unholy_d		t_unholy_d;
union							u_unholy_d
{
	double						d;
	long long					l;
};

typedef union u_unholy_l		t_unholy_l;
union							u_unholy_l
{
	long double					d;
	unsigned char				l[10];
};

typedef struct s_dispatch		t_dispatch;
struct							s_dispatch
{
	int							c;
	int							(*function)(t_format var, int fd);
};

int								ft_printf(const char *str, ...);
void							get_flags(char **str, t_format *variable);
int								is_flag(char c);
int								is_length(char c);
int								is_num(char c);
int								print_string(char *str, va_list list, int fd);
int								ft_printf_dispatch(t_format variable, int fd);
void							pass_num(char **str);
int								check_l_ll(char **str, t_format *variable);
int								check_h_hh(char **str, t_format *variable);
int								check_cl(char **str, t_format *variable);
void							get_length(char **str, t_format *variable);
int								get_spec(char **str, t_format *variable);
void							get_c(va_list list, t_format *variable);
void							get_sp(va_list list, t_format *variable);
void							get_diouxx(va_list list, t_format *variable);
void							get_f(va_list list, t_format *variable);
void							get_variable_value(t_format *variable,
								va_list list);
int								get_all_var_info(char **str, va_list list,
								t_format *variable);
void							print_hex_padding(t_format variable,
								int length, int fd);
void							check_minus_and_zero(t_format *variable);
void							get_hex_length(unsigned long long n,
								int *length);
void							print_hex(unsigned long long n, int c, int fd);
int								get_diouxx_return(t_format var, int length, int neg);
void							cast_hex(t_format variable, int fd);
void							add_hex_prefix(t_format *variable,
								int fd, int *length);
void							cast_hex_length(t_format variable, int *length);
void							print_precision_hex(t_format variable,
								int length, int fd, int neg);
int								printxx(t_format variable, int fd);
void							overwrite_flags(t_format *variable);
int								get_nbr_len(long long n);
int								print_floats(t_format var, int fd);
int								printo(t_format var, int fd);
void							cast_octal(t_format variable, int fd);
void							add_octal_prefix(t_format *variable, int fd);
void							print_octal(unsigned long long n, int fd);
void							get_octal_length(unsigned long long n,
								int *length);
void							cast_octal_length(t_format variable,
								int *length);
char							*ft_lltoa(long long n);
char							*get_mantissa_d(t_format var);
int								get_exponent_d(t_format var);
char							*multiply_string_cm(int mult, char *str);
char							*ft_strjoin_free(char **s1, char **s2,
								int free1, int free2);
void							cast_unsigned_length(t_format variable,
								int *length);
char							*add_string_cm(char *small, char *input,
								int length_large, int length_small);
char							*ft_str_swap_length(char *str1, char *large,
								int *len_lg, int *len_sm);
int								check_f_edge(t_format var, int exponent,
								char *mantissa, int fd);
char							*divide_by_two(char *input, char *temp);
void							print_padding(t_format variable, 
								int length, int neg);
char							*divide_string_cm(int mult, char **input);
char							*ft_strjoin_char(char **s1, char c);
char							*ft_prepend_char(char c, char **s1);
void							check_negative_floats(char **answer,
								t_format var);
char							*ft_ulltoa(unsigned long long n);
void							get_number_length(long long n, int *length);
void							get_unsigned_length(unsigned long long n,
								int *length);
void							print_unsigned(unsigned long long n, int fd);
char							*chop_float_precision(char **answer,
								t_format var, int i);
int								get_decimal_length(char *str);
char							*round_precision(char **answer, int precision,
								int *num, char *temp);
void							cast_unsigned(t_format variable, int fd);
int								is_negative_digit(t_format variable,
								int *length);
void							print_digit_prefix(t_format var,
								int fd, int neg);
int								printu(t_format var, int fd);
int								oxx_is_zero(t_format var);
void							print_digit(long long n, int fd);
void							cast_digit_length(t_format variable,
								int *length);
void							cast_digit(t_format variable, int fd);
int								printd(t_format var, int fd);
void							print_csp_padding(int length,
								int width, int fd);
int								check_d_edge(t_format var, int fd);
int								prints(t_format var, int fd);
int								printc(t_format var, int fd);
int								printp(t_format var, int fd);
int								handle_variable(char **str,
								int fd, va_list list);
int								printpercent(t_format var, int fd);
void							rearrange_float_prefix(t_format var, char *answer);
int								print_float_string(t_format var, char **answer, int fd);
int								get_used_length(t_format variable, int length, int neg);
void							get_diouxx2(va_list, t_format *variable);
int								d_only_zero(t_format var, int fd);
#endif
