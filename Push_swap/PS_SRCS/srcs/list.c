/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 17:09:21 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/22 11:21:27 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	insert_start(t_node **head, int data)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->data = data;
	new_node->next = (*head);
	new_node->prev = NULL;
	if ((*head) != NULL)
		(*head)->prev = new_node;
	(*head) = new_node;
}

void	insert_end(t_node **head, int data)
{
	t_node	*new_node;
	t_node	*last;

	new_node = (t_node *)malloc(sizeof(t_node));
	last = *head;
	new_node->data = data;
	new_node->next = NULL;
	if (*head == NULL)
	{
		new_node->prev = NULL;
		*head = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
	new_node->prev = last;
}

int	remove_first(t_node **head)
{
	t_node	*to_delete;
	int		data;

	data = -1;
	if ((*head) != NULL)
	{
		to_delete = (*head);
		(*head) = (*head)->next;
		if ((*head) != NULL)
			(*head)->prev = NULL;
		data = to_delete->data;
		free(to_delete);
	}
	return (data);
}

int	remove_last(t_node **head)
{
	t_node	*temp;
	t_node	*last_node;
	int		data;

	data = -1;
	if ((*head) != NULL)
	{
		if ((*head)->next == NULL)
			*head = NULL;
		else
		{
			temp = *head;
			while (temp->next->next != NULL)
				temp = temp->next;
			last_node = temp->next;
			data = last_node->data;
			temp->next = NULL;
			free(last_node);
		}
	}
	return (data);
}

void	ft_putlist(t_node *head)
{
	while (head)
	{
		ft_putnbr_fd(head->data, 1);
		ft_putchar_fd('\n', 1);
		head = head->next;
	}
}
