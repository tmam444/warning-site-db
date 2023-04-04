/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:19:04 by chulee            #+#    #+#             */
/*   Updated: 2023/04/04 15:21:27 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H
# include <sys/types.h>

unsigned int	ntk_hash_first(const void *__key, const size_t table_size);
unsigned int	ntk_hash_second(const void *__key, const size_t table_size);
unsigned int	ntk_hash_third(const void *__key, const size_t table_size);

#endif
