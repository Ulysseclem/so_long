/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:21:42 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 10:33:41 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

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
