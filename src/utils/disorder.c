/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:17:11 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static double	count_mistakes(t_stack *node, double *pairs)
{
	t_stack	*next;
	double	mistakes;

	mistakes = 0.0;
	next = node->next;
	while (next)
	{
		*pairs += 1.0;
		if (node->value > next->value)
			mistakes += 1.0;
		next = next->next;
	}
	return (mistakes);
}

double	compute_disorder(t_stack *stack)
{
	double	mistakes;
	double	total_pairs;

	if (!stack || !stack->next)
		return (0.0);
	mistakes = 0.0;
	total_pairs = 0.0;
	while (stack)
	{
		mistakes += count_mistakes(stack, &total_pairs);
		stack = stack->next;
	}
	return (mistakes / total_pairs);
}

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}
