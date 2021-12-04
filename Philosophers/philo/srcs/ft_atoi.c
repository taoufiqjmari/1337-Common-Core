/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 14:39:19 by tjmari            #+#    #+#             */
/*   Updated: 2021/10/14 10:06:46 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

static _Bool	check_int_limit(long result)
{
	if (result > 2147483647)
		return (1);
	return (0);
}

static _Bool	final_check(const char *str, int i)
{
	if (str[i] != '\0' || is_empty(str))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if (check_int_limit(result))
			return (-2);
		i++;
	}
	if (final_check(str, i))
		return (-2);
	return (result);
}
