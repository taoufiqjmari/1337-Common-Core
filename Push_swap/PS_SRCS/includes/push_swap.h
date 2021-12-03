/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:54:28 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/21 20:01:04 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>	// write(2), read(2)
# include <stdlib.h>	// malloc(3), free(3), exit(3)
# include "../../libft/libft.h"

typedef struct s_node
{
	int				data;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_utils
{
	int		counter;
	int		to_push;
	int		min;
	int		max;
	int		mid;
	int		wanted;
	_Bool	side;
}	t_utils;

void	switch_input(t_node **stack_a);
int		what_index(t_node *stack_a, int data);

void	insert_start(t_node **head, int data);
void	insert_end(t_node **head, int data);
int		remove_first(t_node **head);
int		remove_last(t_node **head);
void	ft_putlist(t_node *head);
int		lst_size(t_node *stack);
t_node	*copy_list(t_node *head);
t_node	*last_elm(t_node *stack);
int		last_elm_data(t_node *stack);
int		smallest_elm(t_node *stack);
void	free_list(t_node *head);

void	ft_sa(t_node **stack_a);
void	ft_sb(t_node **stack_b);
void	ft_ss(t_node **stack_a, t_node **stack_b);
void	ft_pa(t_node **stack_a, t_node **stack_b);
void	ft_pb(t_node **stack_a, t_node **stack_b);
void	ft_ra(t_node **stack_a);
void	ft_rb(t_node **stack_b);
void	ft_rr(t_node **stack_a, t_node **stack_b);
void	ft_rra(t_node **stack_a);
void	ft_rrb(t_node **stack_b);
void	ft_rrr(t_node **stack_a, t_node **stack_b);

void	to_sort(t_node **stack_a, t_node **stack_b);
_Bool	which_side(t_node *stack, int min, int max);
void	wanted_to_top(t_node **stack_a, t_node **stack_b, t_utils u, _Bool opt);
void	bring_back_posb(t_node **stack_a, t_node **stack_b, t_utils u);
_Bool	is_in(t_node *stack, int data);
void	fake_lst_elm(t_node **stack);
void	fix_lst_elm(t_node **stack);

#endif
