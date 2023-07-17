/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 10:57:22 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 09:47:40 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <inttypes.h>

int		ft_printf(const char *str, ...);

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putchar_fd_int(char c, int fd);
int		ft_putnbr(long int i);

int		ft_hexa(unsigned int nb, char type);
int		ft_hexaconverter(unsigned int nb);
int		ft_hexaconverter_maj(unsigned int nb);

int		ft_putptr(uintptr_t num);
void	ft_print_ptr(uintptr_t num);
int		ft_ptr_len(uintptr_t num);

int		ft_unsigned(unsigned int i);

// static char	*ft_rev(char *str);
// static int	count(long int n);
// static char	*ft_modulo_i(long int n, char *str, int neg);
char	*ft_itoa(int nb);
size_t	ft_strlen(const char *s);

#endif
