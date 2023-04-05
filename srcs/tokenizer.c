/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 18:39:08 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 16:43:44 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "warning_site_db_table.h"

void	free_tokens(char **tokens)
{
	ntk_strsplit_free(tokens);
}

char**	ntk_tokenizer(char *url, const char delimiter, e_token_status *status, int *token_length)
{
	int		length = 0;
	char	**tokens;

	tokens = ntk_strsplit(url, delimiter);
	while (tokens[length] != NULL)
		length++;
	*token_length = length;
	if (length < 12)
		*status = TOKEN_STATUS_ERROR;
	else if (length == 12 || (length == 13 && strcmp(tokens[3], tokens[4]) == 0))
		*status = TOKEN_STATUS_NORMAL;
	else
		*status = TOKEN_STATUS_ABNORMAL;
	return (tokens);
}

bool	set_file_and_path(site_info *ret, char *url, char **tokens)
{
    int		str_size;
    char	*path_token = tokens[2];
    char	*path_start_point, *path;
    char	*file_start_point, *file;

    // Find file start point and extract file
    file_start_point = ntk_strrstr(url, path_token);
	if (file_start_point == NULL)
		return (false);
    str_size = strlen(file_start_point) - 16; // 16 str length = ,4,4,0,0,0,0,I,P
    file = malloc(str_size + 1);
    assert(file != NULL);
    strncpy(file, file_start_point, str_size);
    file[str_size] = '\0';
    ret->file = file;

    // Find path start point and extract path
    path_start_point = strstr(url, path_token);
	if (path_start_point == NULL)
		return (false);
    str_size = file_start_point - path_start_point - 1;
	if (str_size <= 0)
		return (false);
    path = malloc(str_size + 1);
	assert(path != NULL);
    strncpy(path, path_start_point, str_size);
    path[str_size] = '\0';
    ret->path = path;
    return (true);
}

site_info	*ntk_make_info(char *url, char **tokens, char **key, e_token_status token_status, const int length)
{
	site_info	*ret;

	ret = malloc(sizeof(site_info));
	assert(ret != NULL);
	memset(ret, 0, sizeof(site_info));
	*key = ntk_strdup(tokens[0]);
	ret->port = atoi(tokens[1]);
	if (token_status == TOKEN_STATUS_NORMAL)
	{
		ret->path = ntk_strdup(tokens[2]);
		ret->file = ntk_strdup(tokens[3]);
	}
	else
	{
		if (set_file_and_path(ret, url, tokens) == false)
		{
			free(*key);
			free_info(ret);
			return (NULL);
		}
	}
	ret->nude = atoi(tokens[length - 8]);
	ret->sex = atoi(tokens[length - 7]);
	ret->violence = atoi(tokens[length - 6]);
	ret->language = atoi(tokens[length - 5]);
	ret->etc1 = atoi(tokens[length - 4]);
	ret->etc2 = atoi(tokens[length - 3]);
	ret->status = tokens[length - 2][0] == 'I' ? INSERT : DELETE;
	ret->type = tokens[length - 1][0] == 'S' ? SUB_DIRECTORY : PAGE;
	return (ret);
}

site_info	*ntk_parser(char *url, char **key)
{
	e_token_status	token_status;
	int				token_length;
	site_info		*ret;
	char			**tokens;

	tokens = ntk_tokenizer(url, ',', &token_status, &token_length);
	if (token_status == TOKEN_STATUS_ERROR)
	{
		free_tokens(tokens);
		return (NULL);
	}
	ret = ntk_make_info(url, tokens, key, token_status, token_length);
	free_tokens(tokens);
	return (ret);
}
