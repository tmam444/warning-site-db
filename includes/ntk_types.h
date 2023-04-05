/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ntk_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:55:23 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 17:02:49 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NTK_TYPES_H
# define NTK_TYPES_H
# include "table.h"
# include "list.h"

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
	Table			**tables;
	unsigned int	table_size;
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

#endif
