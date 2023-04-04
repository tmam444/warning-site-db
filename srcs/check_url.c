/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_url.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:30:59 by chulee            #+#    #+#             */
/*   Updated: 2023/04/04 19:01:16 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

struct url_struct {
	char	*domain;
	char	*path;
	char	*file;
};

// https://search.naver.com/search.naver?where=nexearch&sm=top_hty&fbm=1&ie=utf8&query=test

/*
struct url_struct*	make_url_struct(char *host, char *urn, int port)
{
	const char			*http = "http://", *https = "https://", *www = "www.", *str_port;
	char				*host_check_point = host, *urn_check_point = urn;
	bool				is_start_www = false;
	struct url_struct	*ret;

	ret = malloc(sizeof(struct url_struct));
	assert(ret != NULL);
	str_port = ntk_strjoin(":", itoa(str_port));
	if (strncmp(host_check_point, www, strlen(www)) == 0)
	{
		is_start_www = true;
		host_check_point += strlen(www);
	}
	ret->file = ntk_strdup(urn);
	urn_check_point = strchr(urn, '.');
	urn_check_point = strchr(urn_check_point, '?');
	if (urn_check_point)
		ret->path = ntk_strndup(urn, urn_check_point - urn - 1);
	else
		ret->path = ntk_strdup(urn);
	if (port == 443)
		ret->domain = ntk_strjoin(https, is_start_www ? host_check_point : urn);
	else
		ret->domain = ntk_strjoin(http, is_start_www ? host_check_point : urn);
	ret->domain = ntk_strjoin(ret->domain, 
	return (ret);
}
*/

bool	ntk_check_url(char *host, char *urn, int port)
{
	struct url_struct	*s_url;
	bool				ret = false;

	// s_url = make_url_struct(url, port);

	return (ret);
}
