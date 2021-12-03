/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:35:28 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 11:26:23 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_ra(t_node **stack_a)
{
	int	data;

	data = remove_first(stack_a);
	if (data >= 0)
		insert_end(stack_a, data);
	ft_putendl_fd("ra", 1);
}

void	ft_rb(t_node **stack_b)
{
	int	data;

	data = remove_first(stack_b);
	if (data >= 0)
		insert_end(stack_b, data);
	ft_putendl_fd("rb", 1);
}

void	ft_rr(t_node **stack_a, t_node **stack_b)
{
	ft_ra(stack_a);
	ft_rb(stack_b);
	ft_putendl_fd("rr", 1);
}
