/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 10:38:59 by uclement          #+#    #+#             */
/*   Updated: 2023/06/29 17:18:25 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "so_long.h"


char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_stock(&stock, fd);
	if (stock == NULL)
		return (NULL);
	to_line(stock, &line);
	free_stock(&stock);
	if (line[0] == '\0')
	{
		free (stock);
		stock = NULL;
		free (line);
		return (NULL);
	}
	return (line);
}

void	read_stock(char **stock, int fd)
{
	char		*buf;
	int			size;
	int			c;

	c = 0;
	buf = NULL;
	size = 1;
	while (c != 1 && size != 0)
	{	
		buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!buf)
			return ;
		size = read(fd, buf, BUFFER_SIZE);
		if (size < 0)
		{
			free (buf);
			return ;
		}
		buf[size] = '\0';
		*stock = gnl_strjoin(*stock, buf);
		c = check_newline(buf);
		free (buf);
	}
	return ;
}

void	to_line(char *stock, char **line)
{
	int		i;
	int		j;

	i = 0;
	while (stock[i] && stock[i] != '\n')
		i++;
	if (stock[i] == '\n')
		i++;
	*line = malloc(sizeof(char) * (i + 1));
	if (!*line)
		return ;
	j = 0;
	while (j < i)
	{
		(*line)[j] = stock[j];
		j++;
	}
	(*line)[j] = '\0';
}

void	free_stock(char **stock)
{
	char	*temp;
	int		len;
	int		i;
	int		j;

	i = 0;
	len = ft_strlen(*stock);
	while ((*stock)[i] != '\n' && (*stock)[i])
		i++;
	j = 0;
	temp = malloc(sizeof(char) * (len - i) + 1);
	if (temp == NULL)
		return ;
	while (i < len)
		temp[j++] = (*stock)[++i];
	temp[j] = '\0';
	free(*stock);
	*stock = temp;
}

/*#include <stdio.h>
int main()
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open("foo1.txt", O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		printf("%s",line);
		if (line == NULL)
		{	
			free(line);
			break ;
		}
		free(line);
		i++;
	}
	close(fd);

	line = NULL;

	while ((line = get_next_line(0)))
	{
		printf("%s\n", line);
		free(line);
	}

	return (0);
}*/
