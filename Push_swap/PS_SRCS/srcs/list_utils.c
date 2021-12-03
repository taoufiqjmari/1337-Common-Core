/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 20:27:58 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/20 20:28:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	lst_size(t_node *stack)
{
	int	i;

	i = 0;
	while (stack)
	{
		i++;
		stack = stack->next;
	}
	return (i);
}

t_node	*copy_list(t_node *head)
{
	t_node	*new_node;

	if (head == NULL)
		return (NULL);
	else
	{
		new_node = (t_node *)malloc(sizeof(t_node));
		new_node->data = head->data;
		new_node->next = copy_list(head->next);
		return (new_node);
	}
}

t_node	*last_elm(t_node *stack)
{
	if (stack)
		while (stack->next)
			stack = stack->next;
	return (stack);
}

int	last_elm_data(t_node *stack)
{
	if (stack)
		while (stack->next)
			stack = stack->next;
	return (stack->data);
}

int	smallest_elm(t_node *stack)
{
	int	smallest;

	smallest = 2147483647;
	if (stack)
	{
		while (stack)
		{
			if (stack->data < smallest)
				smallest = stack->data;
			stack = stack->next;
		}
	}
	return (smallest);
}
