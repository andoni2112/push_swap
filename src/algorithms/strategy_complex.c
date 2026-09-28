/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy_complex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:56:56 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:09:52 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max_bits(t_stack *a)
{
	int	max_idx;
	int	max_bits;

	max_idx = stack_size(a) - 1;
	max_bits = 0;
	while ((max_idx >> max_bits) > 0)
		max_bits++;
	return (max_bits);
}

static int	process_bit(t_stack **a, t_stack **b, int bit, int size)
{
	int	i;
	int	ops;

	i = 0;
	ops = 0;
	while (i < size)
	{
		if ((((*a)->index >> bit) & 1) == 1)
			ra(a);
		else
			pb(a, b);
		ops++;
		i++;
	}
	while (*b)
	{
		pa(a, b);
		ops++;
	}
	return (ops);
}

int	strategy_complex(t_stack **a, t_stack **b)
{
	int	bit;
	int	max_bits;
	int	size;
	int	ops;

	if (!a || !*a || is_sorted(*a))
		return (0);
	if (stack_size(*a) <= 5)
		return (sort_small(a, b));
	size = stack_size(*a);
	max_bits = get_max_bits(*a);
	bit = 0;
	ops = 0;
	while (bit < max_bits)
	{
		ops += process_bit(a, b, bit, size);
		bit++;
	}
	return (ops);
}
