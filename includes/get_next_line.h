/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szheng <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 14:48:08 by szheng            #+#    #+#             */
/*   Updated: 2023/04/05 14:24:21 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096

# include <assert.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <string.h>

char*	get_next_line(const int fd);
void	ntk_strsplit_free(char **str_splits);
char**	ntk_strsplit(char const *s, char delimiter);
char*	ntk_strjoin(char const *s1, char const *s2);
char*	ntk_strdup(const char *s1);
char*	ntk_strndup(const char *s1, size_t str_length);
char*	ntk_strrstr(const char *haystack, const char *needle);
char*	ntk_itoa(int n);

#endif
