/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itox.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:03:07 by tjmari            #+#    #+#             */
/*   Updated: 2020/03/12 15:07:40 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	itox_lower(unsigned int num, char **str)
{
	int				i;
	int				mod;
	unsigned int	num2;
	char			*temp;

	num2 = num;
	i = 1;
	while ((num2 = num2 / 16) != 0)
		i++;
	temp = (char*)malloc(i + 1);
	temp[i] = '\0';
	i = 0;
	if (num == 0)
		temp[i] = 0 + 48;
	while (num != 0)
	{
		mod = num % 16;
		temp[i++] = mod < 10 ? mod + 48 : mod + 87;
		num = num / 16;
	}
	*str = temp;
	ft_strrev(str);
}

void	itox_upper(unsigned int num, char **str)
{
	int				i;
	int				mod;
	unsigned int	num2;
	char			*temp;

	num2 = num;
	i = 1;
	while ((num2 = num2 / 16) != 0)
		i++;
	temp = (char*)malloc(i + 1);
	temp[i] = '\0';
	i = 0;
	if (num == 0)
		temp[i] = 0 + 48;
	while (num != 0)
	{
		mod = num % 16;
		temp[i++] = mod < 10 ? mod + 48 : mod + 55;
		num = num / 16;
	}
	*str = temp;
	ft_strrev(str);
}

void	itox_l_uint(unsigned long num, char **str)
{
	int				i;
	int				mod;
	unsigned long	num2;
	char			*temp;

	num2 = num;
	i = 1;
	while ((num2 = num2 / 16) != 0)
		i++;
	temp = (char*)malloc(i + 1);
	temp[i] = '\0';
	i = 0;
	if (num == 0)
		temp[i] = 0 + 48;
	while (num != 0)
	{
		mod = num % 16;
		temp[i++] = mod < 10 ? mod + 48 : mod + 87;
		num = num / 16;
	}
	*str = temp;
	ft_strrev(str);
}
