/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_fin_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 14:56:54 by mmarzouk          #+#    #+#             */
/*   Updated: 2021/06/05 13:44:39 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fin_slash(char **fin, char *s, int *i)
{
	char	hld[2];
	char	*hold;

	hld[1] = 0;
	(*i)++;
	hold = *fin;
	hld[0] = s[(*i)];
	*fin = ft_strjoin(*fin, hld);
	free(hold);
	(*i)++;
}

void	fin_nrml(char **fin, char *s, int *i)
{
	char	hld[2];
	char	*hold;

	hld[1] = 0;
	hold = *fin;
	hld[0] = s[(*i)];
	*fin = ft_strjoin(*fin, hld);
	free(hold);
	(*i)++;
}

void	fin_sngl_q(char **fin, char *s, int *i)
{
	(*i)++;
	while (s[(*i)] != '\'')
		fin_nrml(fin, s, i);
	(*i)++;
}

void	fin_err(char **fin, int *i)
{
	char	*hld;
	char	*tmp;

	(*i)++;
	hld = ft_getvalue("?");
	tmp = *fin;
	*fin = ft_strjoin(tmp, hld);
	free(tmp);
	free(hld);
}

void	fin_vars(char **fin, char *s, int *i)
{
	int		j;
	char	*var;
	char	*hld;

	var = ft_strdup("");
	(*i)++;
	if (s[(*i)] == '?')
		fin_err(fin, i);
	else if (!(ft_isalnum(s[(*i)]) || s[(*i)] == '_') && (*i)--)
		fin_nrml(fin, s, i);
	else
	{
		while (ft_isalnum(s[(*i)]) || s[(*i)] == '_')
			fin_nrml(&var, s, i);
		j = ft_getenv(var);
		if (j != -1)
		{
			free(var);
			var = *fin;
			hld = ft_getvalue(g_tool.envp[j]);
			*fin = ft_strjoin(var, hld);
			free(hld);
		}
	}
	free(var);
}
