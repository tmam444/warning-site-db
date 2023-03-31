/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:22:40 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 16:19:22 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H
# define TABLE_SIZE 10000
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <assert.h>
# include <string.h>

typedef struct Node {
	const void	*key;
	void		*value;
	struct Node	*next;
} Node;

typedef struct Table {
	int				size;
	int				length;
	int				(*cmp)(const void *x, const void *y);
	unsigned int	(*hash)(const void *key);
	struct Node		**buckets;
} Table;

Table*			table_new(unsigned int size, int cmp(const void *x, const void *y), unsigned int hash(const void *key));
void*			table_get(Table *table, const void *key);
void*			table_put(Table *table, const void *key, void *value);
void*			table_remove(Table *table, const void *key);
void			table_free(Table *table);
void			table_free_with_custom_free(Table *table, void (*value_free_function)(void *));
const void**	table_get_key_set(Table *table);

#endif
