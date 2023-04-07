/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:20:05 by chulee            #+#    #+#             */
/*   Updated: 2023/04/06 13:16:36 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash.h"
#include <stdint.h>

static void convert_to_hex_string(unsigned char *input, char *output, int length)
{
    for (int i = 0; i < length; i++)
		sprintf(output + (i * 2), "%02X", input[i]);
}

char*	create_md5(char *host)
{
	char			*result;
	unsigned char	encrypt_msg[16];

	GetEncryptedMessage((unsigned char*)host, strlen(host), encrypt_msg);
	result = malloc(sizeof(char) * 33);
	assert(result != NULL);
	convert_to_hex_string(encrypt_msg, result, 16);
	result[32] = '\0';
	return (result);
}

unsigned int	ntk_hash_first(const void *__key, const size_t table_size)
{
	const char		*key = __key;
    unsigned long	hash = 5381;
    int				c;

    while ((c = *key++))
        hash = (((hash << 5) + hash) + c);
    return (hash % table_size);
}

unsigned int	ntk_hash_second(const void *__key, const size_t table_size)
{
	const char		*key = __key;
   	unsigned long	hash = 7963;
    int 			c;

    while ((c = *key++))
        hash = (((hash << 5) + hash) + c);
    return (hash % table_size);
}

unsigned int	ntk_hash_third(const void *__key, const size_t table_size)
{
	const char		*key = __key;
   	unsigned long	hash = 9157;
    int 			c;

    while ((c = *key++))
        hash = (((hash << 5) + hash) + c);
    return (hash % table_size);
}
