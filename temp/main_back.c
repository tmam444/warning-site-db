/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:08 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 13:47:00 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

typedef struct count {
	int	d;
	int	p;
} count;

int	main(void)
{
	int			fd, i;
	count		*prev_value, *new_value, *cur_value;
	char		*line, *key = NULL;
	Table		*table;
	site_info	*info;
	const void	**keys;

	fd = open("./00000000.txt", O_RDONLY);
	assert(fd >= 0);
	table = new_table(TABLE_SIZE, ntk_compare, ntk_hash);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		info = ntk_parser(line, &key);
		ntk_put_table(table, key, info);
		/*
		printf("url = %s\n", line);
		printf("key = %s, port=%d, path=%s, file=%s, nude=%d, sex=%d, vio=%d, lang=%d, etc1=%d, etc2=%d, status=%c, type=%c\n", \
				key, info->port, info->path, info->file, info->nude, info->sex, info->violence, \
				info->language, info->etc1, info->etc2, info->status, info->type);
		*/
		// printf("url = %s, key = %s\n",line, key);
		new_value = malloc(sizeof(count));
		assert(new_value != NULL);
		prev_value = get_table(table, key);
		if (prev_value == NULL)
			memset(new_value, 0, sizeof(count));
		else
			memcpy(new_value, prev_value, sizeof(count));
		if (info->type == SUB_DIRECTORY)
			new_value->d++;
		else
			new_value->p++;
		// printf("%s, S=%d, P=%d\n", key, new_value->d, new_value->p);
		prev_value = put_table(table, key, new_value);
		if (prev_value != NULL)
		{
			free(key);
			free(prev_value);
		}

		if (info)
		{
			if (info->file)
				free(info->file);
			if (info->path)
				free(info->path);
			free(info);
		}
		if (line)
			free(line);
		i++;
		printf("cur i = %d\n", i);
		if (i == 5000)
			break ;
	}

	keys = get_table_key_set(table);
	i = 0;
	while (keys[i] != NULL)
	{
		printf("keys[i] = %s\n", (char *)keys[i]);
		cur_value = get_table(table, keys[i]);
		printf("%s, S=%d, P=%d\n", (char *)keys[i], cur_value->d, cur_value->p);
		i++;
	}
	free(keys);

	free_table(table);
	
	return (0);
}
