/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:54:55 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 11:21:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static _Bool	args_sorted(int argc, char *argv[])
{
	int	i;

	i = 2;
	while (i <= argc - 1)
	{
		if (ft_atoi(argv[i]) < ft_atoi(argv[i - 1]))
			return (0);
		i++;
	}
	return (1);
}

static _Bool	check_args(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = i + 1;
		while (argv[j])
		{
			if (atoi(argv[i]) == atoi(argv[j]))
			{
				ft_putendl_fd("Error", 2);
				return (0);
			}
			j++;
		}
		i++;
	}
	if (args_sorted(argc, argv))
		return (0);
	return (1);
}

static void	fill_stack(int argc, char *argv[], t_node **stack_a)
{
	int	i;

	i = argc - 1;
	while (i > 0)
	{
		insert_start(stack_a, ft_atoi(argv[i]));
		i--;
	}
}

int	main(int argc, char *argv[])
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 2)
		ft_atoi(argv[1]);
	if (check_args(argc, argv))
	{
		fill_stack(argc, argv, &stack_a);
		switch_input(&stack_a);
		to_sort(&stack_a, &stack_b);
	}
	free_list(stack_a);
	return (0);
}
