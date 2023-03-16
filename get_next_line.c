/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhovhann <vhovhann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 16:32:39 by vhovhann          #+#    #+#             */
/*   Updated: 2023/02/23 17:10:07 by vhovhann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_str_line_next(char *s)
{
	int		i;
	int		k;
	char	*str;

	i = 0;
	k = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
	{
		free(s);
		return (NULL);
	}
	str = (char *)malloc(ft_strlen(s) - i + 1);
	if (!str)
		return (NULL);
	i++;
	while (s[i])
		str[k++] = s[i++];
	str[k] = '\0';
	free(s);
	return (str);
}

char	*ft_save_line(char *s)
{
	int		i;
	int		k;
	char	*line;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] && s[i] == '\n')
		i++;
	line = (char *)malloc(i + 1);
	if (!line)
		return (NULL);
	k = 0;
	i = 0;
	while (s[i] && s[i] != '\n')
		line[k++] = s[i++];
	if (s[i] == '\n')
		line[k++] = s[i++];
	line[k] = '\0';
	return (line);
}

char	*ft_str_save(int fd, char *str_line)
{
	int			value;
	char		*buff;

	buff = (char *)malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	value = 1;
	while (!ft_strchr(str_line, '\n') && value != 0)
	{
		value = read(fd, buff, BUFFER_SIZE);
		if (value < 0)
		{
			free(buff);
			return (NULL);
		}
		buff[value] = '\0';
		str_line = ft_strjoin(str_line, buff);
	}
	free(buff);
	return (str_line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	str_line = ft_str_save(fd, str_line);
	if (!str_line)
		return (NULL);
	line = ft_save_line(str_line);
	str_line = ft_str_line_next(str_line);
	if (line && !line[0])
	{
		free(line);
		return (0);
	}
	return (line);
}
