/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_url.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:30:59 by chulee            #+#    #+#             */
/*   Updated: 2023/04/03 15:26:54 by chulee           ###   ########.fr       */
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
struct url_struct*	make_url_struct(char *url, int port)
{
	const char			*http = "http://", *https = "https://", *www = "www.";
	char				*check_point = url;
	bool				is_start_http = false, is_start_www = false;
	struct url_struct	*ret;

	ret = malloc(sizeof(struct url_struct));
	assert(ret != NULL);
	if (strncmp(url, http, strlen(http)) == 0)
	{
		is_start_http = true;
		check_point += strlen(http);
	}
	else if (strncmp(url, https, strlen(https)) == 0)
	{
		is_start_http = true;
		check_point += strlen(https);
	}
	if (strncmp(check_point, www, strlen(www)) == 0)
	{
		is_start_www = true;
		check_point += strlen(www);
	}
	ret->file = ntk_strdup(strchr(check_point, '?'));
	ret->directory = ntk_strndup(strchr(check_point, '/'), strchr(check_point, '?') - check_point);
	if (is_start_http)
	{
		if (is_start_www)
		{
		}
		else
		{
			
		}
	}
	else
	{
		if (port == 443)
		{
			if (is_start_www)
			{
				ret = ntk_strjoin(https, url);
			}
			else
			{
				ret = ntk_strjoin(https, url);
			}
		}
		else
			ret = ntk_strjoin(http, url);
	}
	if (is_start_http == false)
	{
	}
	return (ret);
}
*/

bool	ntk_check_url(char *url, int port)
{
	struct url_struct	*s_url;
	bool				ret = false;

	// s_url = make_url_struct(url, port);

	return (ret);
}
