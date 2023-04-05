/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:08 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 13:53:14 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

unsigned int	collision_count[TABLE_COUNT];

ntk_table*	create_ntk_table(void)
{
	ntk_table		*ret;
	unsigned int	(*hash_arr[TABLE_COUNT])(const void *key, const size_t table_size) = { ntk_hash_first, ntk_hash_second, ntk_hash_third };

	ret = ntk_table_new(TABLE_SIZE, TABLE_COUNT, TABLE_RATIO, ntk_compare, hash_arr);
	return (ret);
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

void	check_test(ntk_table *table)
{
	url_info	*url;

	url = create_url_struct("www.metart.com", "/account", 443);
	printf("domain = %s, path = %s, file = %s\n", url->domain, url->path, url->file);
	ntk_check_url(url, table);
	url = create_url_struct("www.metart.com", "/account/", 443);
	printf("domain = %s, path = %s, file = %s\n", url->domain, url->path, url->file);
	ntk_check_url(url, table);
}

void	file_read(int argc, char *argv[], ntk_table *table)
{
	char		*line, *key;
	site_info	*info;
	int			fd, i;

	for (i = 0; i < argc; i++)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			fprintf(stderr, "Not Found File: %s\n", argv[i]);
			continue;
		}
		while ((line = get_next_line(fd)) != NULL)
		{
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
		}
	}
	printf("setup complete\n");

}

int	main(int argc, char *argv[])
{
	ntk_table	*table;

	table = create_ntk_table();
	file_read(argc, argv, table);
	check_test(table);
	// print_all(table);
	printf("clear~~\n");
	clear(table);
	printf("1차 : %d, 2차 : %d, 3차 : %d\n", collision_count[0], collision_count[1], collision_count[2]);
	return (0);
}
