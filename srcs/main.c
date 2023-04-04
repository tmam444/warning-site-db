/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:08 by chulee            #+#    #+#             */
/*   Updated: 2023/04/04 18:27:50 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

unsigned int	collision_count[TABLE_COUNT];

void	setup(ntk_table *table)
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
		{
			free(line);
			continue;
		}
		if (info->status == INSERT)
			ntk_table_put(table, key, info);
		else
			ntk_table_remove(table, key);
		free(line);
		if (i % 1000000 == 0)
			printf("read : %d\n", i);
		i++;
	}
	printf("setup complete\n");
}

void	clear(ntk_table *table)
{
	ntk_table_free(table);
}

void	print_all(ntk_table *table)
{
	int			max_directory, max_page, temp_directory_size, avg_page, avg_directory, len_page, len_directory;
	int			total_count = 0;
	const void	**keys;
	domain_info	*info;
	int			i, j;

	for (j = 0; j < table->table_size; j++)
	{
		max_directory = max_page = avg_page = avg_directory = len_page = len_directory = 0;
		keys = table_get_key_set(table->tables[j]);
		i = 0;
		while (keys[i] != NULL)
		{
			info = table_get(table->tables[j], keys[i]);
			temp_directory_size = list_length(info->directory);
			// printf("keys[i] = %s, info.directory.length = %d, info.page.length = %d\n", (char *)keys[i], temp_directory_size, info->page->length);
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
			total_count += temp_directory_size;
			total_count += info->page->length;
		}
		printf("max_directory = %d, max_page = %d\n", max_directory, max_page);
		printf("avg_directory = %f, avg_page = %f\n", (double)avg_directory / len_directory, (double)avg_page / len_page);
		// printf("count = %d\n", 
		free(keys);
		// sleep(3);
	}
	printf("total_count = %d\n", total_count);
}

int	main(void)
{
	ntk_table	*table;
	unsigned int (*hash_arr[TABLE_COUNT])(const void *key, const size_t table_size) = { ntk_hash_first, ntk_hash_second, ntk_hash_third };

	table = ntk_table_new(TABLE_SIZE, TABLE_COUNT, TABLE_RATIO, ntk_compare, hash_arr);
	setup(table);
	print_all(table);
	printf("clear~~\n");
	clear(table);
	printf("1차 : %d, 2차 : %d, 3차 : %d\n", collision_count[0], collision_count[1], collision_count[2]);
	return (0);
}
