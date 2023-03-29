/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   site_db_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:54:12 by chulee            #+#    #+#             */
/*   Updated: 2023/03/29 18:22:19 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

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

void	ntk_put_table(Table *table, const char *__key, site_info *__value)
{
	char		*key = malloc(strlen(__key) + 1);
	site_info	*prev_value;

	assert(key != NULL);
	strcpy(key, __key);
	prev_value = put_table(table, __key, __value);
	if (prev_value != NULL)
		free(prev_value);
}

void	ntk_remove_table(Table *table, const char *__key)
{
	site_info	*delete_value;

	assert(table != NULL && __key != NULL);
	delete_value = remove_table(table, __key);
	if (delete_value != NULL)
		free(delete_value);
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
