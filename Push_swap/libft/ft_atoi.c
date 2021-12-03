/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:49:48 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/21 17:07:35 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static _Bool	is_empty(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i])
		return (0);
	return (1);
}

static void	check(long result, int sign)
{
	if ((result > 2147483648 && sign == -1)
		|| (result > 2147483647 && sign == 1))
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
}

static void	final_check(const char *str, int i)
{
	if ((ft_strlen(str) == 1 && !(*str >= '0' && *str <= '9'))
		|| str[i] != '\0' || is_empty(str))
	{
		ft_putendl_fd("Error", 2);
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		check(result, sign);
		i++;
	}
	final_check(str, i);
	return (result * sign);
}
