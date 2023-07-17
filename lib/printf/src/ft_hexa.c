/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:53:21 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 09:42:06 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexaconverter(unsigned int nb)
{
	int		len;
	char	*hex;

	len = 0;
	hex = "0123456789abcdef";
	if (nb >= 16)
	{
		ft_hexaconverter(nb / 16);
		ft_hexaconverter(nb % 16);
	}
	else
		len += ft_putchar_fd_int(hex[nb], 1);
	return (len);
}

int	ft_hexaconverter_maj(unsigned int nb)
{
	char	*hex;
	int		len;

	len = 0;
	hex = "0123456789ABCDEF";
	if (nb >= 16)
	{
		ft_hexaconverter_maj(nb / 16);
		ft_hexaconverter_maj(nb % 16);
	}
	else
		len += ft_putchar_fd_int(hex[nb], 1);
	return (len);
}

int	ft_hexa(unsigned int nb, char type)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (write(1, "0", 1));
	else if (type == 'x')
		ft_hexaconverter(nb);
	else if (type == 'X')
		ft_hexaconverter_maj(nb);
	while (nb != 0)
	{
		len++;
		nb = nb / 16;
	}
	return (len);
}
