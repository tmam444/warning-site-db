/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_url.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 17:30:59 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 19:03:57 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

const char*	make_encoding_url(char *url, int port)
{
	const char	*http = "http://", *https = "https://", *www = "www.", *ret = NULL;
	char		*check_point = url;
	bool		is_start_http = false, is_start_www = false;

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

bool	ntk_check_url(char *url, int port)
{
	const char	*encoding_url;
	bool		ret = false;

	encoding_url = make_encoding_url(url, port);

	return (ret);
}
