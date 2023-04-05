/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_url.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:30:59 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 16:58:14 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "warning_site_db_table.h"

void	print_site_info(site_info *info)
{
	printf("port=%d, path=%s, file=%s, nude=%d, sex=%d,", info->port, info->path, info->file, info->nude, info->sex);
	printf("vio=%d, lang=%d, etc1=%d, etc2=%d, status=%c, type=%c\n", info->violence, info->language, info->etc1, info->etc2, \
																	info->status, info->type);
}

static url_info*	create_url_struct(char *host, char *urn, int port)
{
    const char	*http = "http://", *https = "https://", *www = "www.";
    char		*host_check_point = host, *urn_check_point = urn;
	char		*suffix, *temp;
    bool		is_start_www = false;
    url_info	*url;

    url = malloc(sizeof(url_info));
    assert(url != NULL);
    temp = ntk_itoa(port);
    suffix = ntk_strjoin(":", temp);
    free(temp);

    if (strncmp(host_check_point, www, strlen(www)) == 0)
    {
        is_start_www = true;
        host_check_point += strlen(www);
    }

    url->file = ntk_strdup(urn);
    urn_check_point = strchr(urn, '.');
	if (urn_check_point)
	    urn_check_point = strchr(urn_check_point, '?');

    if (urn_check_point)
        url->path = ntk_strndup(urn, urn_check_point - urn - 1);
    else
        url->path = ntk_strdup(urn);

    if (port == 443)
        url->domain = ntk_strjoin(https, is_start_www ? host_check_point : host);
    else
        url->domain = ntk_strjoin(http, is_start_www ? host_check_point : host);

    temp = ntk_strjoin(url->domain, suffix);
	free(suffix);
    free(url->domain);
    url->domain = temp;

    return (url);
}

int	ntk_directory_compare(const char *x, const char *y)
{
	const char *str_x = x;
	const char *str_y = y;

	while (*str_x != '\0' || *str_y != '\0')
	{
		if (*str_x == '\0' || *str_y == '\0')
			if (*str_x == '/' || *str_y == '/')
				return (0);
		if (*str_x != *str_y)
			return (*str_x - *str_y);
		str_x++;
		str_y++;
	}
	return (0);
}

site_info*	ntk_directory_search(List *lst, const char *key)
{
	site_info	*value;

	while (lst != NULL)
	{
		value = lst->value;
		if (ntk_directory_compare(value->path, key) == 0)
			return (value);
		lst = lst->next;
	}
	return (NULL);
}

site_info*	ntk_search(url_info *url, ntk_table *table)
{
	domain_info		*info;
	site_info		*temp, *value = NULL;
	char			*hash;

	hash = create_md5(url->domain);
	printf("hash = %s\n", hash);
	info = ntk_table_get(table, hash);
	free(hash);
	if (info)
	{
		temp = ntk_directory_search(info->directory, url->path);
		if (temp)
			value = temp;
		temp = table_get(info->page, url->file);
		if (temp)
			value = temp;
	}
	return  (value);
}

bool	ntk_check_url(char *host, char *urn, int port, ntk_table *table)
{
	bool		ret = false;
	site_info	*value;
	url_info	*url;

	url = create_url_struct(host, urn, port);
	value = ntk_search(url, table);
	if (value)
	{
		print_site_info(value);
		ret = true;
	}
	free_url_info(url);
	return (ret);
}
