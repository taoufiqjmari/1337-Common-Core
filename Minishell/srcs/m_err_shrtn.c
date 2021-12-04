/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_err_shrtn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 11:42:11 by mmarzouk          #+#    #+#             */
/*   Updated: 2021/06/05 13:45:55 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int	ft_red(char *s)
{
	if (same(s, "<") || same(s, ">") || same(s, ">>"))
		return (0);
	return (1);
}

void	cmd_arg(int *f, int *i)
{
	(*f) = 1;
	(*i)++;
}

int	redirct_tkn(int *f, int *i, char **sp)
{
	if (!sp[(*i) + 1] || ft_red(sp[(*i)]))
		return (err_quit("minishell: syntax error \n", 258));
	if (itis(sp[(*i) + 1]) != 0)
		return (err_quit("minishell: syntax error \n", 258));
	if (backslash(sp[(*i) + 1]))
		return (1);
	(*f) = 1;
	(*i) += 2;
	return (0);
}

int	semicln_tkn(int *f, int *i)
{
	if (!(*f))
		return (err_quit("minishell: syntax error \n", 258));
	(*f) = 0;
	(*i)++;
	return (0);
}

int	pipe_tkn(int *f, int *i, char **sp)
{
	if (!(*f))
		return (err_quit("minishell: syntax error \n", 258));
	else if (!sp[(*i) + 1])
		return (err_quit("minishell: syntax error \n", 1));
	(*f) = 0;
	(*i)++;
	return (0);
}
