/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   site_db_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:54:12 by chulee            #+#    #+#             */
/*   Updated: 2023/04/04 18:13:57 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"
#include "list.h"
#include "table.h"

domain_info*	create_domain_info(void)
{
	domain_info		*ret;

	ret = malloc(sizeof(domain_info));
	ret->directory = NULL;
	ret->page = table_new(TABLE_PAGE_SIZE, ntk_compare, ntk_hash_first);
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

unsigned int	get_table_size(unsigned int entry_size, unsigned int table_size, double ratio, unsigned int index)
{
	unsigned int	ret;

	if (table_size == 1)
		return (entry_size);
	ret = entry_size * (1 - ratio) / (1 - pow(ratio, table_size));
	ret = ret * pow(ratio, index);
	return (ret);
}

ntk_table*		ntk_table_new(unsigned int entry_size, unsigned int table_size, double ratio, int cmp(const void *x, const void *y), \
											unsigned int (**hash_arr)(const void *key, const size_t table_size))
{
	ntk_table		*ret;
	unsigned int	i;

	ret = malloc(sizeof(ntk_table));
	assert(ret != NULL);
	ret->table_size = table_size;
	ret->tables = malloc(sizeof(Table) * table_size);
	assert(ret->tables != NULL);
	for (i = 0; i < table_size; i++)
		ret->tables[i] = table_new(get_table_size(entry_size, table_size, ratio, i), cmp, hash_arr[i]);
	return (ret);
}

void*	ntk_table_get(ntk_table *table, const char *key)
{
	void			*ret = NULL;
	unsigned int	i;

	for (i = 0; i < TABLE_COUNT; i++)
	{
		ret = table_get(table->tables[i], key);
		if (ret)
			break;
	}
	return (ret);
}

unsigned int	ntk_table_get_insert_index(ntk_table *table, const char *key)
{
	unsigned int		i, ret, index;
	bool				exist = false;
	Node				*node;
	Table				*cur_table;

	for (i = 0; i < TABLE_COUNT; i++)
	{
		cur_table = table->tables[i];
		index = cur_table->hash(key, cur_table->size);
		if (cur_table->buckets[index] == NULL)
		{
			ret = i;
			break ;
		}
		for (node = cur_table->buckets[index]; node != NULL; node = node->next)
		{
			if (cur_table->cmp(node->key, key) == 0)
			{
				ret = i;
				exist = true;
				break;
			}
		}
		if (exist)
			break;
		collision_count[i]++;
	}
	if (i == TABLE_COUNT)
		ret = table->tables[0]->hash(table, TABLE_COUNT);
	return (ret);
}

void	ntk_table_put(ntk_table *table, char *key, site_info *info)
{
	domain_info		*value = ntk_table_get(table, key), *prev_domain_info = NULL;
	site_info		*prev_info;
	unsigned int	insert_index;
	char			*page_key;

	assert(key != NULL && table != NULL && info != NULL);
	if (value == NULL)
		value = create_domain_info();
	if (info->type == SUB_DIRECTORY)
		value->directory = list_push(value->directory, info);
	else
	{
		page_key = ntk_strdup(info->file);
		prev_info = table_put(value->page, page_key, info);
		if (prev_info != NULL)
		{
			free_info(prev_info);
			free(page_key);
		}
	}
	insert_index = ntk_table_get_insert_index(table, key);
	prev_domain_info = table_put(table->tables[insert_index], key, value);
	if (prev_domain_info != NULL)
		free(key);
}

void	ntk_table_remove(ntk_table *table, const char *key)
{
	site_info		*delete_value;
	unsigned int	i;

	assert(table != NULL && key != NULL);
	for (i = 0; i < TABLE_COUNT; i++)
	{
		delete_value = table_remove(table->tables[i], key);
		if (delete_value != NULL)
			free_domain_info(delete_value);
	}
}

void	ntk_table_free(ntk_table *table)
{
	unsigned int	i;

	if (table)
	{
		if (table->tables)
		{
			for (i = 0; i < table->table_size; i++)
			{
				if (table->tables[i])
					table_free_with_custom_free(table->tables[i], free_domain_info);
			}
			free(table->tables);
		}
		free(table);
	}
}
