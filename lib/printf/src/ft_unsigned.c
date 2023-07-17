/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:05:01 by uclement          #+#    #+#             */
/*   Updated: 2023/07/17 09:44:34 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_rev(char *str)
{
	long int		i;
	long int		j;
	char			tmp;

	i = 0;
	j = ft_strlen(str);
	while (i < j / 2)
	{
		tmp = str[i];
		str[i] = str[j - i - 1];
		str[j - i - 1] = tmp;
		i++;
	}
	return (str);
}

static int	count(long int n)
{
	long int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static char	*ft_modulo(long int n, char *str)
{
	int		i;
	char	temp;

	i = 0;
	if (n == 0)
	{
		str[i] = '0';
		i++;
	}
	while (n > 0)
	{
		temp = n % 10 + '0';
		str[i] = temp;
		n = n / 10;
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_uitoa(unsigned int nb)
{
	char			*str;
	unsigned int	n;

	n = nb;
	str = malloc(sizeof(char) * (count(n) + 1));
	if (!str)
		return (NULL);
	str = ft_modulo(n, str);
	return (ft_rev(str));
}

int	ft_unsigned(unsigned int i)
{
	char	*str;
	int		j;

	j = 0;
	str = ft_uitoa(i);
	while (str[j])
	{
		ft_putchar(str[j]);
		j++;
	}
	free(str);
	return (j);
}
