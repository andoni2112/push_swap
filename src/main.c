/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:16:38 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_config(t_config *config)
{
	config->flag_simple = 0;
	config->flag_medium = 0;
	config->flag_complex = 0;
	config->flag_adaptive = 0;
	config->flag_bench = 0;
}

static int	execute_strategy(t_stack **a, t_stack **b, t_config *config)
{
	if (config->flag_simple)
		return (strategy_simple(a, b));
	if (config->flag_medium)
		return (strategy_medium(a, b));
	if (config->flag_complex)
		return (strategy_complex(a, b));
	return (strategy_adaptive(a, b));
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_config	config;
	double		disorder;
	int			ops;

	if (argc < 2)
		return (0);
	a = NULL;
	b = NULL;
	init_config(&config);
	parse_input(argc, argv, &a, &config);
	index_stack(a);
	disorder = compute_disorder(a);
	ops = execute_strategy(&a, &b, &config);
	print_benchmark(&config, disorder, ops);
	free_stack(&a);
	free_stack(&b);
	return (0);
}
