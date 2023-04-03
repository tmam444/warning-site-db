/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:08 by chulee            #+#    #+#             */
/*   Updated: 2023/04/03 18:54:11 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.h"
#include "site_db_table.h"
#include "table.h"

void	setup(Table *table)
{
	const char	*filename = "./00000000.txt";
	char		*line, *key;
	site_info	*info;
	int			fd, i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "Not Found File: %s\n", filename);
		exit(1);
	}
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		// printf("i = %d, line = %s\n", ++i, line);
		info = ntk_parser(line, &key);
		if (info == NULL)
			continue;
		if (info->status == INSERT)
			ntk_table_put(table, key, info);
		else
			ntk_table_remove(table, key);
		free(line);
	}
	printf("setup complete\n");
}

void	clear(Table *table)
{
	table_free_with_custom_free(table, free_domain_info);
}

void	print_all(Table *table)
{
	int			max_directory, max_page, temp_directory_size, avg_page, avg_directory, len_page, len_directory;
	const void	**keys;
	domain_info	*info;
	int			i;

	max_directory = max_page = avg_page = avg_directory = len_page = len_directory = 0;
	keys = table_get_key_set(table);
	i = 0;
	while (keys[i] != NULL)
	{
		info = table_get(table, keys[i]);
		temp_directory_size = list_length(info->directory);
		// printf("keys[i] = %s, info.directory.length = %d, info.page.length = %d\n", (char *)keys[i], temp_directory, info->page->length);
		if (0 < temp_directory_size)
			len_directory++;
		if (0 < info->page->length)
			len_page++;
		if (max_directory < temp_directory_size)
			max_directory = temp_directory_size;
		if (max_page < info->page->length)
			max_page = info->page->length;
		avg_page += info->page->length;
		avg_directory += temp_directory_size;
		i++;
	}
	printf("max_directory = %d, max_page = %d\n", max_directory, max_page);
	printf("avg_directory = %f, avg_page = %f\n", (double)avg_directory / len_directory, (double)avg_page / len_page);
	free(keys);
}

int	main(void)
{
	Table			*table;

	table = table_new(TABLE_SIZE, ntk_compare, ntk_hash);
	setup(table);
	print_all(table);
	clear(table);
	return (0);
}
