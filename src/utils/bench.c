/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:23:14 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_two_digits(int value)
{
	if (value < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(value, 2);
}

static void	print_strategy(t_config *config, double disorder)
{
	ft_putstr_fd("[bench] strategy:   ", 2);
	if (config->flag_simple)
		ft_putstr_fd("Simple / O(n^2)\n", 2);
	else if (config->flag_medium)
		ft_putstr_fd("Medium / O(n*sqrt(n))\n", 2);
	else if (config->flag_complex)
		ft_putstr_fd("Complex / O(n log n)\n", 2);
	else if (disorder < 0.2)
		ft_putstr_fd("Adaptive / low disorder\n", 2);
	else if (disorder < 0.5)
		ft_putstr_fd("Adaptive / O(n*sqrt(n))\n", 2);
	else
		ft_putstr_fd("Adaptive / O(n log n)\n", 2);
}

void	print_benchmark(t_config *config, double disorder, int total_ops)
{
	int	whole;
	int	decimals;

	if (!config->flag_bench)
		return ;
	whole = (int)(disorder * 100);
	decimals = (int)(disorder * 10000) % 100;
	ft_putstr_fd("[bench] disorder:   ", 2);
	ft_putnbr_fd(whole, 2);
	ft_putchar_fd('.', 2);
	print_two_digits(decimals);
	ft_putstr_fd("%\n", 2);
	print_strategy(config, disorder);
	ft_putstr_fd("[bench] total_ops:  ", 2);
	ft_putnbr_fd(total_ops, 2);
	ft_putchar_fd('\n', 2);
}
