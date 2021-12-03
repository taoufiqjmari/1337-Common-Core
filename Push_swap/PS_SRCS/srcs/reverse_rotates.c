/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:37:36 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 11:25:22 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_rra(t_node **stack_a)
{
	int	data;

	data = remove_last(stack_a);
	if (data >= 0)
		insert_start(stack_a, data);
	ft_putendl_fd("rra", 1);
}

void	ft_rrb(t_node **stack_b)
{
	int	data;

	data = remove_last(stack_b);
	if (data >= 0)
		insert_start(stack_b, data);
	ft_putendl_fd("rrb", 1);
}

void	ft_rrr(t_node **stack_a, t_node **stack_b)
{
	ft_rra(stack_a);
	ft_rrb(stack_b);
	ft_putendl_fd("rrr", 1);
}
