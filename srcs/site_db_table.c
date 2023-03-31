/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   site_db_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:54:12 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 16:55:02 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"
#include "list.h"
#include "table.h"

domain_info*	create_domain_info(void)
{
	domain_info	*ret;

	ret = malloc(sizeof(domain_info));
	ret->directory = NULL;
	ret->page = table_new(TABLE_SIZE, ntk_compare, ntk_hash);
	return (ret);
}

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

int	ntk_compare(const void *x, const void *y)
{
	const char *str_x = x;
	const char *str_y = y;

	while (*str_x != '\0' || *str_y != '\0')
	{
		if (*str_x != *str_y)
			return (*str_x - *str_y);
		str_x++;
		str_y++;
	}
	return (0);
}

void	ntk_table_put(Table *table, const char *key, site_info *info)
{
	domain_info	*value = table_get(table, key);
	site_info	*prev_info;

	assert(key != NULL && table != NULL && info != NULL);
	if (value == NULL)
		value = create_domain_info();
	if (info->type == SUB_DIRECTORY)
		value->directory = list_push(value->directory, info);
	else
	{
		prev_info = table_put(value->page, ntk_strdup(info->file), info);
		if (prev_info != NULL)
			free_info(prev_info);
	}
	table_put(table, key, value);
}

void	ntk_table_remove(Table *table, const char *__key)
{
	site_info	*delete_value;

	assert(table != NULL && __key != NULL);
	delete_value = table_remove(table, __key);
	if (delete_value != NULL)
		free(delete_value);
}

void	ntk_table_free(Table *table)
{
	if (table)
		table_free_with_custom_free(table, free_domain_info);
}

unsigned int	ntk_hash(const void *__key)
{
	const char		*key = __key;
    unsigned long	hash = 5381;
    int c;

    while ((c = *key++))
        hash = (((hash << 5) + hash) + c) % TABLE_SIZE;
    return (hash);
}
