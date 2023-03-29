/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 13:22:40 by chulee            #+#    #+#             */
/*   Updated: 2023/03/29 15:56:05 by chulee           ###   ########.fr       */
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

Table*			new_table(unsigned int size, int cmp(const void *x, const void *y), unsigned int hash(const void *key));
void*			get_table(Table *table, const void *key);
void*			put_table(Table *table, const void *key, void *value);
void*			remove_table(Table *table, const void *key);
void			free_table(Table *table);
const void**	key_set(Table *table);

#endif
