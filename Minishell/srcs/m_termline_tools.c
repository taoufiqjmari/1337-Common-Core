/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_termline_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/05 13:23:02 by mmarzouk          #+#    #+#             */
/*   Updated: 2021/06/08 15:07:54 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del(void)
{
	char	*tmp;

	tmp = g_tool.trm->curr;
	g_tool.trm->curr = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
	g_tool.trm->h_cur = tgetstr("le", NULL);
	ft_putstr_fd(g_tool.trm->h_cur, 1);
	g_tool.trm->h_cur = tgetstr("cd", NULL);
	ft_putstr_fd(g_tool.trm->h_cur, 1);
	free (tmp);
}

void	up(int *i)
{
	if ((*i) == 0 || !doublecount(g_tool.trm->line))
		return ;
	(*i)--;
	if ((*i) == (doublecount(g_tool.trm->line) - 1))
		g_tool.trm->last = ft_strdup(g_tool.trm->curr);
	free(g_tool.trm->curr);
	g_tool.trm->curr = ft_strdup(g_tool.trm->line[(*i)]);
}

void	down(int *i)
{
	if ((*i) == doublecount(g_tool.trm->line) || !doublecount(g_tool.trm->line))
		return ;
	if ((*i) == ((doublecount(g_tool.trm->line) - 1)) && g_tool.trm->last)
	{
		free(g_tool.trm->curr);
		g_tool.trm->curr = ft_strdup(g_tool.trm->last);
		(*i)++;
		free(g_tool.trm->last);
		g_tool.trm->last = NULL;
		return ;
	}
	(*i)++;
	free(g_tool.trm->curr);
	g_tool.trm->curr = ft_strdup(g_tool.trm->line[(*i)]);
}

void	print_exit_quit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

int	single_q(char *s, int *i)
{
	int	f;

	f = 1;
	while (s[++(*i)])
	{
		if (s[(*i)] == '\'')
		{
			f = 0;
			break ;
		}
	}
	if (f)
	{	
		ft_putstr_fd("parse error : close the quotes !!\n", 2);
		return (seterr(1));
	}
	return (0);
}
