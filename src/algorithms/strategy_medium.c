/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_medium.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:23:00 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	push_chunk(t_stack **a, t_stack **b, int index)
{
	if ((*a)->index <= index)
	{
		pb(a, b);
		rb(b);
		return (2);
	}
	pb(a, b);
	return (1);
}

static int	push_chunks_to_b(t_stack **a, t_stack **b, int chunk)
{
	int	i;
	int	ops;

	i = 0;
	ops = 0;
	while (*a)
	{
		if ((*a)->index <= i + chunk)
		{
			ops += push_chunk(a, b, i);
			i++;
		}
		else
		{
			ra(a);
			ops++;
		}
	}
	return (ops);
}

static int	move_max_to_top(t_stack **b, int max_idx)
{
	int	pos;
	int	ops;

	pos = get_index_pos(*b, max_idx);
	ops = 0;
	while ((*b)->index != max_idx)
	{
		if (pos <= stack_size(*b) / 2)
			rb(b);
		else
			rrb(b);
		ops++;
	}
	return (ops);
}

static int	push_back_to_a(t_stack **a, t_stack **b)
{
	int	max_idx;
	int	ops;

	ops = 0;
	while (*b)
	{
		max_idx = stack_size(*b) - 1;
		ops += move_max_to_top(b, max_idx);
		pa(a, b);
		ops++;
	}
	return (ops);
}

int	strategy_medium(t_stack **a, t_stack **b)
{
	int	chunk;
	int	size;
	int	ops;

	if (!a || !*a || is_sorted(*a))
		return (0);
	if (stack_size(*a) <= 5)
		return (sort_small(a, b));
	size = stack_size(*a);
	chunk = 1;
	while (chunk <= size / chunk)
		chunk++;
	chunk--;
	ops = push_chunks_to_b(a, b, chunk);
	ops += push_back_to_a(a, b);
	return (ops);
}
