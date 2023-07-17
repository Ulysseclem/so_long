/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:38:42 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 09:42:09 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ptr_len(uintptr_t num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

int	ft_putptr(uintptr_t num)
{
	int	len;

	if (num == 0)
	{
		write(1, "(nil)", 5);
		len = 5;
	}
	else
	{
		len = 2;
		write (1, "0x", 2);
		ft_print_ptr(num);
		len += ft_ptr_len(num);
	}
	return (len);
}

void	ft_print_ptr(uintptr_t num)
{
	if (num >= 16)
	{
		ft_print_ptr(num / 16);
		ft_print_ptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd_int((num + '0'), 1);
		else
			ft_putchar_fd_int((num - 10 + 'a'), 1);
	}
}
