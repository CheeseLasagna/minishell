/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 16:52:38 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 16:52:40 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		free_mem(char **ptr1, char **ptr2, char *remainder[], int result)
{
	int i;

	if (ptr1)
	{
		free(*ptr1);
		*ptr1 = NULL;
	}
	if (ptr2)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	i = 0;
	while (remainder && i <= 15000)
	{
		if (remainder[i])
		{
			free(remainder[i]);
			remainder[i] = NULL;
		}
		i++;
	}
	return (result);
}

int		update_remainder(char *remainder[], int fd, char **line)
{
	char	*new_line;
	char	*tmp;

	new_line = ft_strchr(remainder[fd], '\n');
	*new_line = '\0';
	if (!(*line = ft_strdup(remainder[fd])))
		return (free_mem(line, NULL, remainder, -1));
	new_line++;
	tmp = remainder[fd];
	if (*new_line == '\0')
		remainder[fd] = NULL;
	else if (!(remainder[fd] = ft_strdup(new_line)))
		return (free_mem(line, &tmp, remainder, -1));
	free(tmp);
	return (1);
}

int		line_from_remainder(char *remainder[], int fd, char **line, char **buf)
{
	free(*buf);
	*buf = NULL;
	if (!remainder[fd])
	{
		if (!(*line = ft_strdup("\0")))
			return (free_mem(NULL, NULL, remainder, -1));
		return (0);
	}
	if (ft_strchr(remainder[fd], '\n'))
		return (update_remainder(remainder, fd, line));
	if (!(*line = ft_strdup(remainder[fd])))
		return (free_mem(NULL, NULL, remainder, -1));
	free(remainder[fd]);
	remainder[fd] = NULL;
	return (0);
}

int		set_remainder(char *remainder[], int fd, char **buf)
{
	char	*tmp;

	if (!remainder[fd])
	{
		if (!(remainder[fd] = ft_strdup(*buf)))
			return (0);
		return (1);
	}
	if (!(tmp = ft_strjoin(remainder[fd], *buf)))
		return (0);
	free(remainder[fd]);
	remainder[fd] = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	static char	*remainder[15000];
	long int	readen;

	if (!line || BUFFER_SIZE < 1 || BUFFER_SIZE > 2147483646
		|| fd < 0 || read(fd, 0, 0) || !(buf = malloc(BUFFER_SIZE + 1)))
		return (-1);
	while (!ft_strchr(remainder[fd], '\n'))
	{
		if ((readen = read(fd, buf, BUFFER_SIZE)) == -1)
			return (free_mem(line, &buf, remainder, -1));
		if (readen == 0)
			return (line_from_remainder(remainder, fd, line, &buf));
		buf[readen] = '\0';
		if (!(set_remainder(remainder, fd, &buf)))
			return (free_mem(&buf, NULL, remainder, -1));
	}
	return (line_from_remainder(remainder, fd, line, &buf));
}
