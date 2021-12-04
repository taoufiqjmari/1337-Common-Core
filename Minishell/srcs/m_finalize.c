/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_finalize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 09:46:38 by mmarzouk          #+#    #+#             */
/*   Updated: 2021/06/05 13:41:23 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_getenv(char *s)
{
	int		i;
	char	**env;
	char	**splt;

	i = -1;
	env = g_tool.envp;
	while (env && env[++i])
	{
		splt = ft_split(env[i], '=');
		if (same(s, splt[0]))
		{
			doublefree(splt);
			return (i);
		}
		doublefree(splt);
	}
	return (-1);
}

void	fin_quote(char **fin, char *s, int *i)
{
	(*i)++;
	while (s[(*i)] != '\"')
	{
		if (s[(*i)] == '\\' && ft_strchr("\\\"$", s[(*i) + 1]))
			fin_slash(fin, s, i);
		else if (s[(*i)] == '\\' && !ft_strchr("\\\"$", s[(*i) + 1]))
		{
			fin_nrml(fin, s, i);
			fin_nrml(fin, s, i);
		}
		else if (s[(*i)] == '$')
			fin_vars(fin, s, i);
		else
			fin_nrml(fin, s, i);
	}
	(*i)++;
}

char	*fin_line(char	*s)
{
	int		i;
	char	*fin;

	i = 0;
	fin = ft_strdup("");
	while (s[i])
	{
		if (s[i] == '\\')
			fin_slash(&fin, s, &i);
		else if (s[i] == '\"')
			fin_quote(&fin, s, &i);
		else if (s[i] == '\'')
			fin_sngl_q(&fin, s, &i);
		else if (s[i] == '$')
			fin_vars(&fin, s, &i);
		else
			fin_nrml(&fin, s, &i);
	}
	return (fin);
}

void	fin_lines(char	**strs)
{
	char	*s;
	int		inc;

	inc = -1;
	while (strs[++inc])
	{
		s = fin_line(strs[inc]);
		free(strs[inc]);
		strs[inc] = s;
	}
}

void	finalizem(int i)
{
	while (g_tool.cmd[i]->args || g_tool.cmd[i]->file)
	{
		if (g_tool.cmd[i]->args)
			fin_lines(g_tool.cmd[i]->args);
		if (g_tool.cmd[i]->file)
			fin_lines(g_tool.cmd[i]->file);
		if (same(g_tool.cmd[i]->sep, NULL) || same(g_tool.cmd[i]->sep, ";"))
			break ;
		else
			i++;
	}
}
