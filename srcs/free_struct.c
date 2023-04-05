/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:39:28 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 14:49:05 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

void	free_info(void *__info)
{
	site_info	*info = (site_info *)__info;

	if (info->path)
		free(info->path);
	if (info->file)
		free(info->file);
	free(info);
}

void	free_domain_info(void *__info)
{
	domain_info	*info = (domain_info *)__info;

	if (info)
	{
		if (info->directory)
			list_free_with_custom_free(info->directory, free_info);
		if (info->page)
			table_free_with_custom_free(info->page, free_info);
		free(info);
	}
}

void	free_url_info(url_info *url)
{
	if (url)
	{
		if (url->domain)
			free(url->domain);
		if (url->path)
			free(url->path);
		if (url->file)
			free(url->file);
		free(url);
	}
}
