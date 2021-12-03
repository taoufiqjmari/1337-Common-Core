/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 07:49:30 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 11:48:30 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

static void	wrong_op(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(255);
}

static void	what_op(const char *op, t_node **stack_a, t_node **stack_b)
{
	if (!(ft_strcmp(op, "sa")))
		ft_sa(stack_a);
	else if (!(ft_strcmp(op, "sb")))
		ft_sb(stack_b);
	else if (!(ft_strcmp(op, "ss")))
		ft_ss(stack_a, stack_b);
	else if (!(ft_strcmp(op, "pa")))
		ft_pa(stack_a, stack_b);
	else if (!(ft_strcmp(op, "pb")))
		ft_pb(stack_a, stack_b);
	else if (!(ft_strcmp(op, "ra")))
		ft_ra(stack_a);
	else if (!(ft_strcmp(op, "rb")))
		ft_rb(stack_b);
	else if (!(ft_strcmp(op, "rr")))
		ft_rr(stack_a, stack_b);
	else if (!(ft_strcmp(op, "rra")))
		ft_rra(stack_a);
	else if (!(ft_strcmp(op, "rrb")))
		ft_rrb(stack_b);
	else if (!(ft_strcmp(op, "rrr")))
		ft_rrr(stack_a, stack_b);
	else
		wrong_op();
}

static _Bool	sorted(t_node *stack)
{
	while (stack && stack->next)
	{
		if (stack->data > stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	final_check(t_node *stack_a, t_node *stack_b)
{
	if (sorted(stack_a) && lst_size(stack_b) == 0)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

void	take_ops(t_node **stack_a, t_node **stack_b)
{
	char	*op;
	char	*to_free;
	char	temp[2];

	op = ft_strdup("");
	temp[1] = '\0';
	while (read(0, temp, 1) > 0)
	{
		if (temp[0] != '\n')
		{
			to_free = op;
			op = ft_strjoin(op, temp);
			free(to_free);
		}
		else
		{
			what_op(op, stack_a, stack_b);
			to_free = op;
			op = ft_strdup("");
			free(to_free);
		}
	}
	free(op);
	final_check((*stack_a), (*stack_b));
}
