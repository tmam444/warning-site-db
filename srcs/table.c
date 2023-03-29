/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:01:28 by chulee            #+#    #+#             */
/*   Updated: 2023/03/29 16:02:36 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

Table*	new_table(unsigned int _size, int _cmp(const void *x, const void *y), \
					unsigned int _hash(const void *key))
{
	Table			*ret;
	unsigned int	i;

	assert(_size > 0 && _cmp != NULL && _hash != NULL);
	ret = malloc(sizeof(Table));
	assert(ret != NULL);
	ret->length = 0;
	ret->size = _size;
	ret->cmp = _cmp;
	ret->hash = _hash;
	ret->buckets = malloc(sizeof(Node) * _size);
	assert(ret->buckets != NULL);
	for (i = 0; i < _size; i++)
		ret->buckets[i] = NULL;
	return (ret);
}

void*	get_table(Table *table, const void *key)
{
	void			*value = NULL;
	Node			*node;
	unsigned int	index;

	assert(table != NULL && key != NULL);
	index = table->hash(key);
	for (node = table->buckets[index]; node != NULL; node = node->next)
		if (table->cmp(node->key, key) == 0)
			break;
	if (node != NULL)
		value = node->value;
	return (value);
}

void*	put_table(Table *table, const void *key, void *value)
{
	void			*prev = NULL;	// return prev value
	Node			*node;
	unsigned int	index;
	
	assert(table != NULL && key != NULL);
	index = table->hash(key);
	for (node = table->buckets[index]; node != NULL; node = node->next)
		if (table->cmp(node->key, key) == 0)
			break;
	if (node == NULL)
	{
		node = malloc(sizeof(Node));
		assert(node != NULL);
		node->key = key;
		node->next = table->buckets[index];
		table->buckets[index] = node;
		table->length++;
	}
	else 
		prev = node->value;
	node->value = value;
	return (prev);
}

void*	remove_table(Table *table, const void *key)
{
	void			*delete_value = NULL;	//return value;
	Node			**current_node;
	Node			*temp_node;
	unsigned int	index;

	assert(table != NULL && key != NULL);
	index = table->hash(key);
	for (current_node = &table->buckets[index]; *current_node != NULL; current_node = &(*current_node)->next)
	{
		if (table->cmp((*current_node)->key, key) == 0)
		{
			temp_node = *current_node;
			if (temp_node->key)
				free((void *)temp_node->key);
			delete_value = temp_node->value;
			*current_node = temp_node->next;
			free(temp_node);
			table->length--;
			break;
		}
	}
	return (delete_value);
}

void	free_table(Table *table)
{
	int		i;
	Node	*node, *temp;

	if (table)
	{
		if (table->buckets)
		{
			for (i = 0; i < table->size; i++)
			{
				node = table->buckets[i];
				while (node != NULL)
				{
					if (node->key)
						free((void *)node->key);
					if (node->value)
						free(node->value);
					temp = node->next;
					free(node);
					node = temp;
				}
			}
			free(table->buckets);
		}
		free(table);
	}
}

const void**	key_set(Table *table)
{
	const void	**ret = malloc(sizeof(const void *) * (table->length + 1));
	int			i, j;
	Node		*cur;

	assert(ret != NULL && table != NULL);
	j = 0;
	for (i = 0; i < table->size; i++)
	{
		for (cur = table->buckets[i]; cur != NULL; cur = cur->next)
			ret[j++] = cur->key;
	}
	ret[j] = NULL; // end_point
	return (ret);
}
