/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_else_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 20:44:12 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/21 13:23:48 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

_Bool	which_side(t_node *stack, int min, int max)
{
	t_node	*from_head;
	t_node	*from_tail;

	from_head = stack;
	from_tail = last_elm(stack);
	while (!(from_head->data >= min && from_head->data <= max)
		&& !(from_tail->data >= min && from_tail->data <= max))
	{
		from_head = from_head->next;
		from_tail = from_tail->prev;
	}
	if (from_head->data >= min && from_head->data <= max)
		return (0);
	else
		return (1);
}

void	wanted_to_top(t_node **stack_a, t_node **stack_b, t_utils u, _Bool opt)
{
	if (!opt)
	{
		if (!u.side)
			ft_ra(stack_a);
		else
			ft_rra(stack_a);
	}
	else
	{
		if (!u.side)
			ft_rb(stack_b);
		else
			ft_rrb(stack_b);
	}
}

_Bool	is_in(t_node *stack, int data)
{
	while (stack)
	{
		if (stack->data == data)
			return (1);
		stack = stack->next;
	}
	return (0);
}

void	fake_lst_elm(t_node **stack)
{
	t_node	*head;

	if (stack)
	{
		head = (*stack);
		while (head->next)
			head = head->next;
		head->data = -1;
	}
}

void	fix_lst_elm(t_node **stack)
{
	int		data;
	t_node	*head;

	if (stack)
	{
		head = (*stack);
		while (head)
		{
			if (head->data == -1)
				head->data = data;
			data = head->data;
			head = head->next;
		}
	}
}
