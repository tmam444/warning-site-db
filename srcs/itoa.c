/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 23:57:47 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 10:13:40 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_calc_count(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	i++;
	return (i);
}

static void	ft_recursive_write(int n, char *ret, int *i)
{
	if (n / 10 == 0)
	{
		if (n < 0)
		{
			n *= -1;
			ret[(*i)++] = '-';
		}
		ret[(*i)++] = '0' + n;
		return ;
	}
	ft_recursive_write(n / 10, ret, i);
	n = n % 10;
	if (n < 0)
		n *= -1;
	ret[(*i)++] = '0' + n;
}

char*	ntk_itoa(int n)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(ft_calc_count(n) + 1);
	if (!ret)
		return (NULL);
	ft_recursive_write(n, ret, &i);
	ret[i] = '\0';
	return (ret);
}
