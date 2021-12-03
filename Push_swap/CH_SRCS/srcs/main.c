/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:53:39 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/23 13:51:37 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

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

void	free_list(t_node *head)
{
	t_node	*temp;

	while (head)
	{
		temp = head->next;
		free(head);
		head = temp;
	}
}

int	main(int argc, char *argv[])
{
	t_node	*stack_a;
	t_node	*stack_b;

	stack_a = NULL;
	stack_b = NULL;
	if (argc == 1)
		return (0);
	else if (argc == 2)
	{
		ft_atoi(argv[1]);
		fill_stack(argc, argv, &stack_a);
		take_ops(&stack_a, &stack_b);
	}
	else if (check_args(argc, argv))
	{
		fill_stack(argc, argv, &stack_a);
		take_ops(&stack_a, &stack_b);
	}
	free_list(stack_a);
	return (0);
}
