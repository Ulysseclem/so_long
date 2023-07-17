/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:03:27 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 10:35:55 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(long int i)
{
	char	*str;
	int		j;

	j = 0;
	str = ft_itoa(i);
	while (str[j])
	{
		ft_putchar(str[j]);
		j++;
	}
	free(str);
	return (j);
}

int	ft_which(const char *str, va_list args)
{
	int	len;

	len = 0;
	if (*str == 'd' || *str == 'i')
		len = ft_putnbr(va_arg (args, int));
	else
		return (0);
	return (len);
}


int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;

	len = 0;
	va_start (args, str);
	while (*str)
	{
		if (*str != '%' && str)
		{
			len += ft_putchar(*str);
			str++;
		}
		else
		{
			len += ft_which(str + 1, args);
			str += 2;
		}
	}
	va_end(args);
	return (len);
}
