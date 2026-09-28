/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:23:08 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static long	read_digits(const char *str, int sign)
{
	long	result;
	int		digit;

	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > (LONG_MAX - digit) / 10)
		{
			if (sign < 0)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}

long	ft_atol(const char *str)
{
	int	sign;

	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (read_digits(str, sign));
}

int	is_within_int_limits(long num)
{
	return (num >= INT_MIN && num <= INT_MAX);
}

int	has_duplicates(t_stack *stack)
{
	t_stack	*runner;

	while (stack)
	{
		runner = stack->next;
		while (runner)
		{
			if (stack->value == runner->value)
				return (1);
			runner = runner->next;
		}
		stack = stack->next;
	}
	return (0);
}
