/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_dict.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 20:55:23 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/04 18:39:27 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	These two functions returns key and value of the string \
**	'key=value' respectively.
*/

char	*ft_getkey(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (ft_substr(arg, 0, i));
		i++;
	}
	return (ft_strdup(arg));
}

char	*ft_getvalue(char *arg)
{
	int	i;

	i = 0;
	if (same(arg, "?"))
		return (ft_itoa(g_tool.exit_status));
	while (arg[i])
	{
		if (arg[i] == '=')
			return (ft_substr(arg, i + 1, ft_strlen(arg)));
		i++;
	}
	return (ft_strdup(""));
}
