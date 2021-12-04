/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:52 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/16 15:04:15 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
**	ft_export() func either print the envp of export has no args \
**	or add that arg to the envp.
**	ft_putexport() func sort and print the envp according to its rules.
**	how_many_nodes() func counts the num of args to add based on \
**	whether they are valid and if they already exist.
*/

_Bool	ft_export_valid(char *arg)
{
	char	*key;
	int		i;

	i = 0;
	key = ft_getkey(arg);
	if (ft_isdigit(key[0]) || ft_isempty(key))
	{
		free(key);
		return (0);
	}
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			free(key);
			return (0);
		}
		i++;
	}
	free(key);
	return (1);
}

static int	how_many_nodes(int i)
{
	int		j;
	int		count;
	char	*tmp;

	j = 1;
	count = 0;
	while (j < doublecount(g_tool.cmd[i]->args))
	{
		if (ft_export_valid(g_tool.cmd[i]->args[j]))
		{
			tmp = ft_getkey(g_tool.cmd[i]->args[j]);
			if (ft_getenv(tmp) < 0)
				count++;
			free(tmp);
		}
		else
		{
			ft_puterror("minishell: export: `", g_tool.cmd[i]->args[j],
				"': not a valid identifier");
			g_tool.exit_status = 1;
		}
		j++;
	}
	return (count);
}

static void	sortdcp(char **argv)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (argv[i])
	{
		j = 0;
		while (argv[j])
		{
			if (ft_strcmp(argv[i], argv[j]) < 0)
			{
				temp = argv[i];
				argv[i] = argv[j];
				argv[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	ft_putexport(char **argv, int i)
{
	char	*key;
	char	*value;
	char	*tmp;

	key = ft_strdup("");
	value = ft_strdup("");
	sortdcp(argv);
	while (argv[i])
	{
		tmp = key;
		key = ft_getkey(argv[i]);
		free(tmp);
		tmp = value;
		value = ft_getvalue(argv[i]);
		free(tmp);
		ft_putexport_cases(argv[i], key, value);
		i++;
	}
	free(key);
	free(value);
}

void	ft_export(int i)
{
	int		nodes;
	char	**temp;
	int		envp_len;
	int		args_len;

	g_tool.exit_status = 0;
	temp = ft_dcdup(g_tool.envp, 0);
	nodes = how_many_nodes(i);
	if (doublecount(g_tool.cmd[i]->args) == 1)
		ft_putexport(temp, 0);
	else
	{
		envp_len = doublecount(g_tool.envp);
		args_len = doublecount(g_tool.cmd[g_tool.i]->args) - 1;
		add_node_dc(g_tool.cmd[i]->args, nodes, envp_len, args_len);
	}
	doublefree(temp);
}
