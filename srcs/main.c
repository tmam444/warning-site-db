/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:08 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 17:11:33 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "site_db_table.h"
#include "table.h"

bool	setup(Table *table)
{
	const char	*filename = "./00000000.txt";
	char		*line, *key;
	site_info	*info;
	int			fd, i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Not Found File: %s\n", filename);
		return (false);
	}
	table = table_new(TABLE_SIZE, ntk_compare, ntk_hash);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		info = ntk_parser(line, &key);
		if (info->status == INSERT)
			ntk_table_put(table, key, info);
		else
			ntk_table_remove(table, key);
		free(line);
		i++;
		if (i % 1000 == 0)
			printf("read line count : %d\n", i);
	}
	printf("setup complete\n");
	return (true);
}

int	main(void)
{
	Table		*table;
	const void	**keys;
	domain_info	*info;
	int			i;

	table = table_new(TABLE_SIZE, ntk_compare, ntk_hash);
	setup(table);
	keys = table_get_key_set(table);
	i = 0;
	while (keys[i] != NULL)
	{
		printf("keys[i] = %s\n", (char *)keys[i]);
		info = table_get(table, keys[i]);
		printf("info.directory.length = %d, info.page.length = %d\n", list_length(info->directory), info->page->length);
		i++;
	}
	free(keys);
	table_free_with_custom_free(table, free_domain_info);
	return (0);
}
