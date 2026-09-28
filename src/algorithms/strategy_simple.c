/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:57:50 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:09:09 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_pos(t_stack *a)
{
	int	min_idx;
	int	min_pos;
	int	pos;

	min_idx = a->index;
	min_pos = 0;
	pos = 0;
	while (a)
	{
		if (a->index < min_idx)
		{
			min_idx = a->index;
			min_pos = pos;
		}
		pos++;
		a = a->next;
	}
	return (min_pos);
}

static int	move_min_to_top(t_stack **a, int pos, int size)
{
	int	ops;

	ops = 0;
	if (pos <= size / 2)
	{
		while (pos-- > 0)
		{
			ra(a);
			ops++;
		}
	}
	else
	{
		while (pos++ < size)
		{
			rra(a);
			ops++;
		}
	}
	return (ops);
}

static int	push_mins_to_b(t_stack **a, t_stack **b)
{
	int	pos;
	int	size;
	int	ops;

	ops = 0;
	while (stack_size(*a) > 3 && !is_sorted(*a))
	{
		pos = find_min_pos(*a);
		size = stack_size(*a);
		ops += move_min_to_top(a, pos, size);
		pb(a, b);
		ops++;
	}
	return (ops);
}

int	strategy_simple(t_stack **a, t_stack **b)
{
	int	ops;

	if (!a || !*a || is_sorted(*a))
		return (0);
	if (stack_size(*a) <= 5)
		return (sort_small(a, b));
	ops = push_mins_to_b(a, b);
	ops += sort_three(a);
	while (*b)
	{
		pa(a, b);
		ops++;
	}
	return (ops);
}
