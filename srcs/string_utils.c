/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:23:51 by chulee            #+#    #+#             */
/*   Updated: 2023/04/03 15:25:01 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char*	ntk_strdup(const char *s1)
{
    char	*ret;
    int		i;

    ret = malloc(strlen(s1) + 1);
	assert(ret != NULL);
    i = 0;
    while (s1[i] != '\0')
    {
        ret[i] = s1[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char*	ntk_strndup(const char *s1, size_t str_length)
{
    char	*ret;
    size_t	i;

    ret = malloc(str_length + 1);
	assert(ret != NULL);
    i = 0;
	while (i < str_length)
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
