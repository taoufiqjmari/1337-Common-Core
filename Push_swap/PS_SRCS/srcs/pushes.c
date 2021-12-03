/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:28:30 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 11:24:53 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_pa(t_node **stack_a, t_node **stack_b)
{
	int	data;

	data = remove_first(stack_b);
	if (data >= 0)
		insert_start(stack_a, data);
	ft_putendl_fd("pa", 1);
}

void	ft_pb(t_node **stack_a, t_node **stack_b)
{
	int	data;

	data = remove_first(stack_a);
	if (data >= 0)
		insert_start(stack_b, data);
	ft_putendl_fd("pb", 1);
}
