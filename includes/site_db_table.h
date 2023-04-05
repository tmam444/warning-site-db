/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   site_db_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:06:02 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 16:01:29 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SITE_DB_TABLE_H
# define SITE_DB_TABLE_H
# define TABLE_COUNT 3
# define TABLE_RATIO 0.64
# define TABLE_SIZE 25000000
# define TABLE_PAGE_SIZE 200
# include "table.h"
# include "list.h"
# include "MD5.h"
# include "EnCrypt.h"
# include "get_next_line.h"
# include "hash.h"
# include "debug.h"
# include <math.h>
# include <string.h>

typedef enum {
	SUB_DIRECTORY = 'S',
	PAGE = 'P'
} e_type;

typedef enum {
	TOKEN_STATUS_ERROR,
    TOKEN_STATUS_NORMAL,
    TOKEN_STATUS_ABNORMAL
} e_token_status;

typedef enum {
	INSERT = 'I',
	DELETE = 'D'
} e_status;

typedef enum {
    GRADE_0,
    GRADE_1,
    GRADE_2,
    GRADE_3,
    GRADE_4
} e_grade;

typedef struct ntk_table_struct {
	Table	**tables;
	int		table_size;
} ntk_table;

typedef struct domain_info_struct {
	List	*directory;
	Table	*page;
} domain_info;

typedef struct site_info_struct {
	int			port;
	char		*path;
	char		*file;
	e_grade		nude;
	e_grade		sex;
	e_grade		violence;
	e_grade		language;
	e_grade		etc1;
	e_grade		etc2;
	e_status	status;
	e_type		type;
} site_info;

typedef struct url_info_struct {
	char	*domain;
	char	*path;
	char	*file;
} url_info;

/* Clear Structor Functions */
void		free_info(void *__info);
void		free_domain_info(void *__info);
void		free_url_info(url_info *url);

ntk_table*	ntk_table_new(unsigned int entry_size, unsigned int table_count, double ratio, int cmp(const void *x, const void *y), \
											unsigned int (**hash_arr)(const void *key, const size_t table_size));
char**		ntk_tokenizer(char *url, const char delimiter, e_token_status *status, int *token_size);
site_info*	ntk_parser(char *str, char **key);
int			ntk_compare(const void *x, const void *y);
void		ntk_table_put(ntk_table *table, char *__key, site_info *__value);
void*		ntk_table_get(ntk_table *table, const char *key);
void		ntk_table_remove(ntk_table *table, const char *__key);
void		ntk_table_free(ntk_table *table);

bool		ntk_check_url(char *host, char *urn, int port, ntk_table *table);
url_info*	create_url_struct(char *host, char *urn, int port);

extern unsigned int	collision_count[TABLE_COUNT];

#endif
