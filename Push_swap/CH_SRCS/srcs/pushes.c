/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 19:56:37 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 09:21:28 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h"

void	ft_pa(t_node **stack_a, t_node **stack_b)
{
	int	data;

	data = remove_first(stack_b);
	if (data >= 0)
		insert_start(stack_a, data);
}

void	ft_pb(t_node **stack_a, t_node **stack_b)
{
	int	data;

	data = remove_first(stack_a);
	if (data >= 0)
		insert_start(stack_b, data);
}
