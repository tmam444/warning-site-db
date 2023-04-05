/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:08 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 15:21:45 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "site_db_table.h"

unsigned int	collision_count[TABLE_COUNT];

ntk_table*	create_ntk_table(void)
{
	ntk_table		*ret;
	unsigned int	(*hash_arr[TABLE_COUNT])(const void *key, const size_t table_size) = { ntk_hash_first, ntk_hash_second, ntk_hash_third };

	ret = ntk_table_new(TABLE_SIZE, TABLE_COUNT, TABLE_RATIO, ntk_compare, hash_arr);
	assert(ret != NULL);
	return (ret);
}

/*
void	file_read(int argc, char *argv[], ntk_table *table)
{
	const char	*filename = "00000000.txt";
	char		*line, *key;
	site_info	*info;
	int			fd, i, j;
	argc = 2;

	for (i = 1; i < argc; i++)
	{
		printf("i = %d, argv[i] = %s\n", i, argv[i]);
		fd = open(filename, O_RDONLY);
		if (fd < 0)
		{
			fprintf(stderr, "Not Found File: %s\n", argv[i]);
			continue;
		}
		j = 0;
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
			if (++j % 20000 == 0)
				printf("read count : %d\n", j);
		}
	}
	printf("setup complete\n");
}
*/

void    setup(ntk_table *table)
{
        const char      *filename = "./00000000.txt";
        char            *line, *key;
        site_info       *info;
        int                     fd, i;

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
                if (i % 20000 == 0)
                        printf("read : %d\n", i);
                i++;
        }
        printf("setup complete\n");
}


void	clear(ntk_table *table)
{
	ntk_table_free(table);
}

void	check_test(ntk_table *table)
{
	ntk_check_url("www.metart.com", "/account", 443, table);
	ntk_check_url("www.metart.com", "/account/", 443, table);
}

int	main(int argc, char *argv[])
{
	ntk_table	*table;

	if (argc == 1)
	{
		printf("Usage : %s filename1 filename2 ...\n", argv[0]);
		exit(1);
	}
	table = create_ntk_table();
	setup(table);
	// file_read(argc, argv, table);
	check_test(table);
	clear(table);

	int	i;
	for (i = 0; i < TABLE_COUNT; i++)
		printf("%d차 : %d, ", i, collision_count[i]);
	printf("\n");
	return (0);
}
