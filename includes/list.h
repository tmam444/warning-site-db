/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:49:44 by chulee            #+#    #+#             */
/*   Updated: 2023/03/29 18:54:36 by chulee           ###   ########.fr       */
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

List*	create_list(void *value)
{
	List	*ret;

	ret = (List *)malloc(sizeof(List));
	assert(ret != NULL);
	ret->value = value;
	ret->next = NULL;
	return (ret);
}

List*	list_push(List *lst, void *value)
{
	List	*ret;

	ret = create_list(value);
	ret->next = lst;
	return (ret);
}



#endif
