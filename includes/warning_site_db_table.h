/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   warning_site_db_table.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:06:02 by chulee            #+#    #+#             */
/*   Updated: 2023/04/07 15:34:10 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARNING_SITE_DB_TABLE_H
# define WARNING_SITE_DB_TABLE_H
# define TABLE_COUNT 3
# define TABLE_RATIO 0.095
# define TABLE_SIZE 5000000
# define TABLE_PAGE_SIZE 50
# include "table.h"
# include "list.h"
# include "MD5.h"
# include "EnCrypt.h"
# include "get_next_line.h"
# include "hash.h"
# include "ntk_types.h"
# include "debug.h"
# include <math.h>
# include <string.h>

/* Clear Structor Functions */
void		free_info(void *__info);
void		free_domain_info(void *__info);
void		free_url_info(url_info *url);

/* Table Functions */
ntk_table*	ntk_table_new(unsigned int entry_size, unsigned int table_count, double ratio, int cmp(const void *x, const void *y), \
											unsigned int (**hash_arr)(const void *key, const size_t table_size));
int			ntk_compare(const void *x, const void *y);
void		ntk_table_put(ntk_table *table, char *__key, site_info *__value);
void*		ntk_table_get(ntk_table *table, const char *key);
void		ntk_table_remove(ntk_table *table, const char *__key);
void		ntk_table_free(ntk_table *table);

/* Parser Functions */
site_info*	ntk_parser(char *str, char **key);
char**		ntk_tokenizer(char *url, const char delimiter, e_token_status *status, int *token_size);

/* Check URL Functions */
bool		ntk_check_url(char *host, char *urn, int port, ntk_table *table);

extern unsigned int	collision_count[TABLE_COUNT + 1];

#endif
