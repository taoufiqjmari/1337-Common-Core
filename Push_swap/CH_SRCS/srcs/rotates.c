/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:52:53 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 09:20:42 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_ra(t_node **stack_a)
{
	int	data;

	data = remove_first(stack_a);
	if (data >= 0)
		insert_end(stack_a, data);
}

void	ft_rb(t_node **stack_b)
{
	int	data;

	data = remove_first(stack_b);
	if (data >= 0)
		insert_end(stack_b, data);
}

void	ft_rr(t_node **stack_a, t_node **stack_b)
{
	ft_ra(stack_a);
	ft_rb(stack_b);
}
