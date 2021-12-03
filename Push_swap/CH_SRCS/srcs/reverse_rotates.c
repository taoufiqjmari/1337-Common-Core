/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotates.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:56:02 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 09:21:07 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_rra(t_node **stack_a)
{
	int	data;

	data = remove_last(stack_a);
	if (data >= 0)
		insert_start(stack_a, data);
}

void	ft_rrb(t_node **stack_b)
{
	int	data;

	data = remove_last(stack_b);
	if (data >= 0)
		insert_start(stack_b, data);
}

void	ft_rrr(t_node **stack_a, t_node **stack_b)
{
	ft_rra(stack_a);
	ft_rrb(stack_b);
}
