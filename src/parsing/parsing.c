/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:55:00 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:23:12 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	parse_flags(char *arg, t_config *config)
{
	int	set;

	if (!ft_strcmp(arg, "--bench"))
	{
		config->flag_bench = 1;
		return (1);
	}
	if (ft_strcmp(arg, "--simple") && ft_strcmp(arg, "--medium")
		&& ft_strcmp(arg, "--complex") && ft_strcmp(arg, "--adaptive"))
		return (0);
	set = config->flag_simple || config->flag_medium;
	set = set || config->flag_complex || config->flag_adaptive;
	if (set)
		return (-1);
	if (!ft_strcmp(arg, "--simple"))
		config->flag_simple = 1;
	else if (!ft_strcmp(arg, "--medium"))
		config->flag_medium = 1;
	else if (!ft_strcmp(arg, "--complex"))
		config->flag_complex = 1;
	else
		config->flag_adaptive = 1;
	return (1);
}

static void	process_number(char *str, t_stack **a, char **args)
{
	long		val;
	t_stack		*new_node;

	if (!is_number(str))
	{
		free_split(args);
		print_error(a, NULL);
	}
	val = ft_atol(str);
	if (!is_within_int_limits(val))
	{
		free_split(args);
		print_error(a, NULL);
	}
	new_node = stack_new((int)val);
	if (!new_node)
	{
		free_split(args);
		print_error(a, NULL);
	}
	stack_add_back(a, new_node);
}

static void	parse_split(char *arg, t_stack **a)
{
	char	**args;
	int		i;

	args = ft_split(arg, ' ');
	if (!args || !args[0])
	{
		free_split(args);
		print_error(a, NULL);
	}
	i = 0;
	while (args[i])
	{
		process_number(args[i], a, args);
		i++;
	}
	free_split(args);
}

static void	parse_one(char *arg, t_stack **a, t_config *config)
{
	int	flag_result;

	flag_result = 0;
	if (arg[0] == '-')
		flag_result = parse_flags(arg, config);
	if (flag_result == -1)
		print_error(a, NULL);
	if (flag_result == 1)
		return ;
	if (ft_strchr(arg, ' '))
		parse_split(arg, a);
	else
		process_number(arg, a, NULL);
}

void	parse_input(int argc, char **argv, t_stack **a, t_config *config)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		parse_one(argv[i], a, config);
		i++;
	}
	if (!*a || has_duplicates(*a))
		print_error(a, NULL);
}
