/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:37:56 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 14:55:21 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	sort_three(t_node **stack_a)
{
	if ((*stack_a)->data < (*stack_a)->next->data
		&& (*stack_a)->data < (*stack_a)->next->next->data
		&& (*stack_a)->next->data > (*stack_a)->next->next->data)
	{
		ft_sa(stack_a);
		ft_ra(stack_a);
	}
	else if ((*stack_a)->data > (*stack_a)->next->data
		&& (*stack_a)->data < (*stack_a)->next->next->data)
		ft_sa(stack_a);
	else if ((*stack_a)->data > (*stack_a)->next->data
		&& (*stack_a)->data > (*stack_a)->next->next->data
		&& (*stack_a)->next->data < (*stack_a)->next->next->data)
		ft_ra(stack_a);
	else if ((*stack_a)->data < (*stack_a)->next->data
		&& (*stack_a)->data > (*stack_a)->next->next->data)
		ft_rra(stack_a);
	else if ((*stack_a)->data > (*stack_a)->next->data
		&& (*stack_a)->data > (*stack_a)->next->next->data)
	{
		ft_sa(stack_a);
		ft_rra(stack_a);
	}
}

static void	sort_five(t_node **stack_a, t_node	**stack_b)
{
	int		smallest;
	int		counter;

	counter = 0;
	smallest = smallest_elm((*stack_a));
	while (lst_size((*stack_a)) > 3)
	{
		if ((*stack_a)->data == smallest
			|| (*stack_a)->data == smallest + 1)
		{
			ft_pb(stack_a, stack_b);
			counter++;
		}
		else
			ft_ra(stack_a);
	}
	sort_three(stack_a);
	while (counter)
	{
		ft_pa(stack_a, stack_b);
		counter--;
	}
	if ((*stack_a)->data > (*stack_a)->next->data)
		ft_sa(stack_a);
}

static void	bring_em_back(t_node **stack_a, t_node **stack_b, t_utils u)
{
	fake_lst_elm(stack_a);
	while (lst_size((*stack_b)) > 0)
	{
		u.wanted = (*stack_a)->data - 1;
		bring_back_posb(stack_a, stack_b, u);
	}
	fix_lst_elm(stack_a);
	while ((*stack_a)->data != 0)
		ft_rra(stack_a);
}

void	sort_else(t_node **stack_a, t_node **stack_b)
{
	t_utils	u;

	while (lst_size((*stack_a)) > 5)
	{
		u.to_push = ((lst_size((*stack_a)) - 5) / 3) + 1;
		u.min = smallest_elm((*stack_a));
		u.max = u.min + (u.to_push - 1);
		u.mid = (u.min + u.max) / 2;
		u.counter = 0;
		while (u.counter < u.to_push)
		{
			u.side = which_side((*stack_a), u.min, u.max);
			while (!((*stack_a)->data >= u.min && (*stack_a)->data <= u.max))
				wanted_to_top(stack_a, stack_b, u, 0);
			ft_pb(stack_a, stack_b);
			if ((*stack_b)->data < u.mid)
				ft_rb(stack_b);
			u.counter++;
		}
	}
	sort_five(stack_a, stack_b);
	bring_em_back(stack_a, stack_b, u);
}

void	to_sort(t_node **stack_a, t_node **stack_b)
{
	int	size;

	size = lst_size((*stack_a));
	if (size == 2)
		ft_sa(stack_a);
	else if (size == 3)
		sort_three(stack_a);
	else if (size <= 5)
		sort_five(stack_a, stack_b);
	else
		sort_else(stack_a, stack_b);
}
