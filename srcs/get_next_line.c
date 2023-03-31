/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 13:57:32 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 18:47:05 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char*	ntk_strdup(const char *s1)
{
    char	*ret;
    int		i;

    ret = malloc(strlen(s1) + 1);
    if (!ret)
        return (NULL);
    i = 0;
    while (s1[i] != '\0')
    {
        ret[i] = s1[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char*	ntk_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len = strlen(s1) + strlen(s2);
	str = malloc(len + 1);
	assert(str != NULL);
	strcpy(str, s1);
	strcat(str, s2);
	return (str);
}

static char*	extract_line(char **str_ref, const int read_size)
{
	int		len;
	char	*str = *str_ref;
	char	*ret, *tmp;

	len = 0;
	while (str[len] != '\n' && len < read_size)
		len++;
	if (str[len] == '\n')
	{
		ret = malloc(len + 1);
		assert(ret != NULL);
		strncpy(ret, str, len);
		ret[len] = '\0';
		tmp = ntk_strdup(str + len + 1);
		free(str);
		*str_ref = tmp;
	}
	else
	{
		ret = ntk_strdup(str);
		free(str);
		*str_ref = NULL;
	}
	return (ret);
}

char*	get_next_line(const int fd)
{
	static char	*remaining_str;
	int			read_size;
	char		buff[BUFF_SIZE + 1];
	char		*tmp;

	assert(fd >= 0);
	while ((read_size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[read_size] = '\0';
		if (remaining_str == NULL)
			remaining_str = ntk_strdup(buff);
		else
		{
			tmp = ntk_strjoin(remaining_str, buff);
			free(remaining_str);
			remaining_str = tmp;
		}
		if (strchr(remaining_str, '\n'))
			break ;
	}
	if (read_size <= 0 && remaining_str == NULL)
		return (NULL);
	return (extract_line(&remaining_str, read_size));
}
