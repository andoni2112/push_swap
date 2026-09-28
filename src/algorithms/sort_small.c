/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:18:16 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	sort_three_case(t_stack **a, int top, int mid, int bot)
{
	if (top > mid && mid < bot && top < bot)
	{
		sa(*a);
		return (1);
	}
	if (top > mid && mid > bot)
	{
		sa(*a);
		rra(a);
		return (2);
	}
	if (top > mid && mid < bot && top > bot)
	{
		ra(a);
		return (1);
	}
	return (0);
}

static int	sort_three_last(t_stack **a, int top, int mid, int bot)
{
	if (top < mid && mid > bot && top < bot)
	{
		sa(*a);
		ra(a);
		return (2);
	}
	rra(a);
	return (1);
}

int	sort_three(t_stack **a)
{
	int	top;
	int	mid;
	int	bot;
	int	ops;

	if (!a || !*a || is_sorted(*a))
		return (0);
	if (stack_size(*a) == 2)
	{
		sa(*a);
		return (1);
	}
	top = (*a)->index;
	mid = (*a)->next->index;
	bot = (*a)->next->next->index;
	ops = sort_three_case(a, top, mid, bot);
	if (ops)
		return (ops);
	return (sort_three_last(a, top, mid, bot));
}

static int	push_index_to_b(t_stack **a, t_stack **b, int target)
{
	int	pos;
	int	size;
	int	ops;

	pos = get_index_pos(*a, target);
	size = stack_size(*a);
	ops = 0;
	while ((*a)->index != target)
	{
		if (pos <= size / 2)
			ra(a);
		else
			rra(a);
		ops++;
	}
	pb(a, b);
	return (ops + 1);
}

int	sort_small(t_stack **a, t_stack **b)
{
	int	size;
	int	ops;

	if (!a || !*a || is_sorted(*a))
		return (0);
	size = stack_size(*a);
	if (size <= 3)
		return (sort_three(a));
	ops = push_index_to_b(a, b, 0);
	if (size == 5)
		ops += push_index_to_b(a, b, 1);
	ops += sort_three(a);
	while (*b)
	{
		pa(a, b);
		ops++;
	}
	return (ops);
}
