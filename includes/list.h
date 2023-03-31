/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:49:44 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 16:13:39 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H
# include <stdlib.h>
# include <assert.h>

typedef struct List {
	void		*value;
	struct List	*next;
} List;


List*	list_push(List *lst, void *value);
List*	list_pop(List *lst, void **value);
int		list_length(List *lst);
void	list_free(List *lst);
void	list_free_with_custom_free(List *lst, void (*value_free_function)(void *));

#endif
