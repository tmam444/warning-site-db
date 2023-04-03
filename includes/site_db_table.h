/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   site_db_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:06:02 by chulee            #+#    #+#             */
/*   Updated: 2023/04/03 19:06:54 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SITE_DB_TABLE_H
# define SITE_DB_TABLE_H
# define TABLE_FIRST_SIZE 10000000
# define TABLE_SECOND_SIZE 5000000
# define TABLE_PAGE_SIZE 200
# include "table.h"
# include "list.h"
# include "MD5.h"
# include "EnCrypt.h"
# include "get_next_line.h"
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
	Table	*first_table;
	Table	*second_table;
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

void			free_info(void *__info);
void			free_domain_info(void *__info);
ntk_table*		ntk_new_table(size_t table_size);
Table*			table_new(unsigned int size, int cmp(const void *x, const void *y), \
																unsigned int (*hash)(const void *key, const size_t table_size));
char**			ntk_tokenizer(char *url, const char delimiter, e_token_status *status, int *token_size);
site_info*		ntk_parser(char *str, char **key);
int				ntk_compare(const void *x, const void *y);
void			ntk_table_put(Table *table, const char *__key, site_info *__value);
void			ntk_table_remove(Table *table, const char *__key);
unsigned int	ntk_hash_first(const void *__key, const size_t table_size);
unsigned int	ntk_hash_two(const void *__key, const size_t table_size);

#endif
