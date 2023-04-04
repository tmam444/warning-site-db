/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:20:05 by chulee            #+#    #+#             */
/*   Updated: 2023/04/04 15:20:32 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"

unsigned int	ntk_hash_first(const void *__key, const size_t table_size)
{
	const char		*key = __key;
    unsigned long	hash = 5381;
    int c;

    while ((c = *key++))
        hash = (((hash << 5) + hash) + c);
    return (hash % table_size);
}

unsigned int	ntk_hash_second(const void *__key, const size_t table_size)
{
	const char		*key = __key;
    unsigned long	hash = 7963;
    int c;

    while ((c = *key++))
        hash = (((hash << 5) + hash) + c);
    return (hash % table_size);
}

unsigned int	ntk_hash_third(const void *__key, const size_t table_size)
{
	const char		*key = __key;
    unsigned long	hash = 9157;
    int c;

    while ((c = *key++))
        hash = (((hash << 5) + hash) + c);
    return (hash % table_size);
}
