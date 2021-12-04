/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_tools2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 17:19:33 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 13:20:37 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	err_quit(char *s, int err)
{
	ft_putstr_fd(s, 2);
	return (err);
}

int	backslash(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\\' && !s[i + 1])
			return (err_quit
				("minishell: multiline commands are not supported \n", 1));
		if (s[i] == '\\' && s[i + 1])
			i++;
		i++;
	}
	return (0);
}

short	chk_err(char **sp, int i, int value, int flag)
{
	int	hold;

	hold = 0;
	while (sp && sp[i])
	{
		value = itis(sp[i]);
		if (backslash(sp[i]))
			return (1);
		if (value == 0)
			cmd_arg(&flag, &i);
		else if (value == 1)
			hold = redirct_tkn(&flag, &i, sp);
		else if (value == 2)
			hold = semicln_tkn(&flag, &i);
		else if (value == 3)
			hold = pipe_tkn(&flag, &i, sp);
		else
			i++;
		if (hold)
			return (hold);
	}
	return (0);
}

char	**append_line(char **s, char *line, int free)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (doublecount(s) + 2));
	while (s && s[i])
	{
		new[i] = ft_strdup(s[i]);
		i++;
	}
	new[i] = ft_strdup(line);
	new[i + 1] = NULL;
	if (free)
	{
		doublefree (s);
		nfree (line);
	}
	return (new);
}
