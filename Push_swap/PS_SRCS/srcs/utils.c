/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 20:39:51 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/21 17:54:58 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	what_index(t_node *stack_a, int data)
{
	int	count;

	count = 0;
	while (stack_a)
	{
		if (stack_a->data < data)
			count++;
		stack_a = stack_a->next;
	}
	return (count);
}

void	switch_input(t_node **stack_a)
{
	t_node	*temp;
	t_node	*head;

	head = (*stack_a);
	temp = copy_list((*stack_a));
	while ((*stack_a))
	{
		(*stack_a)->data = what_index(temp, (*stack_a)->data);
		(*stack_a) = (*stack_a)->next;
	}
	(*stack_a) = head;
	free_list(temp);
}

void	bring_back_posb(t_node **stack_a, t_node **stack_b, t_utils u)
{
	if (is_in((*stack_b), u.wanted))
	{
		if ((*stack_b)->data < (*stack_a)->data
			&& (*stack_b)->data > last_elm_data((*stack_a)))
		{
			ft_pa(stack_a, stack_b);
			if ((*stack_a)->data != u.wanted)
				ft_ra(stack_a);
		}
		else
		{
			u.side = which_side((*stack_b), u.wanted, u.wanted);
			wanted_to_top(stack_a, stack_b, u, 1);
		}
	}
	else
		ft_rra(stack_a);
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
