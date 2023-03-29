/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   site_db_table.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:06:02 by chulee            #+#    #+#             */
/*   Updated: 2023/03/29 16:03:17 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SITE_DB_TABLE_H
# define SITE_DB_TABLE_H
# include "table.h"
# include "MD5.h"
# include "EnCrypt.h"
# include <string.h>

typedef enum {
	SUB_DIRECTORY,
	PAGE
} e_type;

typedef enum {
	INSERT,
	DELETE
} e_status;

typedef enum {
    GRADE_0,
    GRADE_1,
    GRADE_2,
    GRADE_3,
    GRADE_4
} e_grade;

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

int				ntk_compare(const void *x, const void *y);
void			ntk_put_table(Table *table, const char *__key, site_info *__value);
void			ntk_remove_table(Table *table, const char *__key);
unsigned int	ntk_hash(const void *__key);

#endif
