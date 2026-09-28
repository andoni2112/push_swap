/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_adaptive.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:56:33 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:10:09 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	linear_pass(t_stack **a)
{
	int	size;
	int	i;
	int	ops;

	size = stack_size(*a);
	i = 0;
	ops = 0;
	while (i < size && !is_sorted(*a))
	{
		if ((*a)->next && (*a)->index > (*a)->next->index)
		{
			sa(*a);
			ops++;
		}
		ra(a);
		ops++;
		i++;
	}
	return (ops);
}

static int	strategy_low(t_stack **a, t_stack **b)
{
	int	ops;
	int	pass;

	ops = 0;
	pass = 0;
	while (pass < 3 && !is_sorted(*a))
	{
		ops += linear_pass(a);
		pass++;
	}
	if (!is_sorted(*a))
		ops += strategy_medium(a, b);
	return (ops);
}

int	strategy_adaptive(t_stack **a, t_stack **b)
{
	double	disorder;

	if (!a || !*a || is_sorted(*a))
		return (0);
	if (stack_size(*a) <= 5)
		return (sort_small(a, b));
	disorder = compute_disorder(*a);
	if (disorder < 0.2)
		return (strategy_low(a, b));
	if (disorder < 0.5)
		return (strategy_medium(a, b));
	return (strategy_complex(a, b));
}
