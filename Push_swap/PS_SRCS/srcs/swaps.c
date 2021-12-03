/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:24:09 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 11:32:24 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_sa(t_node **stack_a)
{
	int	temp;

	if ((*stack_a) && (*stack_a)->next)
	{
		temp = (*stack_a)->data;
		(*stack_a)->data = (*stack_a)->next->data;
		(*stack_a)->next->data = temp;
		ft_putendl_fd("sa", 1);
	}
}

void	ft_sb(t_node **stack_b)
{
	int	temp;

	if ((*stack_b) && (*stack_b)->next)
	{
		temp = (*stack_b)->data;
		(*stack_b)->data = (*stack_b)->next->data;
		(*stack_b)->next->data = temp;
		ft_putendl_fd("sb", 1);
	}
}

void	ft_ss(t_node **stack_a, t_node **stack_b)
{
	ft_sa(stack_a);
	ft_sb(stack_b);
	ft_putendl_fd("ss", 1);
}
