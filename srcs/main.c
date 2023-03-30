/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 14:45:08 by chulee            #+#    #+#             */
/*   Updated: 2023/03/30 19:01:30 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "site_db_table.h"

int	main(void)
{
	int			fd;
	char		*line, *key = NULL;
	site_info	*info;

	fd = open("./00000000.txt", O_RDONLY);
	assert(fd >= 0);
	while ((line = get_next_line(fd)) != NULL)
	{
		info = ntk_parser(line, &key);
		printf("url = %s\n", line);
		printf("key = %s, port=%d, path=%s, file=%s, nude=%d, sex=%d, vio=%d, lang=%d, etc1=%d, etc2=%d, status=%c, type=%c\n", \
				key, info->port, info->path, info->file, info->nude, info->sex, info->violence, \
				info->language, info->etc1, info->etc2, info->status, info->type);
		if (info)
		{
			if (info->file)
				free(info->file);
			if (info->path)
				free(info->path);
			free(info);
		}
		if (key)
			free(key);
		if (line)
			free(line);
		printf("\n");
	}
	return (0);
}
