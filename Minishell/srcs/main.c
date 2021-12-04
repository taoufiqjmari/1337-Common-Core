/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 20:03:07 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/05 13:46:23 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	freeall(void)
{
	int	i;

	i = 0;
	while (i < g_tool.cmd_c)
	{
		doublefree(g_tool.cmd[i]->args);
		free(g_tool.cmd[i]->sep);
		doublefree(g_tool.cmd[i]->red);
		doublefree(g_tool.cmd[i]->file);
		free(g_tool.cmd[i]);
		i++;
	}
	free(g_tool.cmd);
}

static	void	initials(void)
{
	t_trm	*trm;

	change_shlvl();
	unset_oldpwd();
	g_tool.original_fd_in = dup(STDIN_FILENO);
	g_tool.original_fd_out = dup(STDOUT_FILENO);
	signal(SIGINT, signal_int);
	signal(SIGQUIT, signal_quit);
	tgetent(NULL, getenv("TERM"));
	trm = malloc(sizeof(t_trm));
	trm->curr = ft_strdup("");
	trm->last = NULL;
	trm->line = NULL;
	trm->lni = 0;
	g_tool.trm = trm;
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;

	(void)argc;
	(void)argv;
	g_tool.envp = ft_dcdup(envp, 0);
	initials();
	while (1)
	{
		g_tool.pid = 0;
		g_tool.exit_flag = 0;
		ft_putstr_fd("\033[0;36mminishell$\033[0m ", 1);
		term_line(&input, 0);
		if (parsing(input))
		{
			executing();
			freeall();
		}
		free(input);
	}
	return (0);
}
