/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indexation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:22:43 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*get_next_min(t_stack *stack)
{
	t_stack	*min_node;

	min_node = NULL;
	while (stack)
	{
		if (stack->index == -1)
		{
			if (!min_node || stack->value < min_node->value)
				min_node = stack;
		}
		stack = stack->next;
	}
	return (min_node);
}

void	index_stack(t_stack *stack)
{
	t_stack	*min_node;
	int		index;

	index = 0;
	min_node = get_next_min(stack);
	while (min_node)
	{
		min_node->index = index;
		index++;
		min_node = get_next_min(stack);
	}
}
