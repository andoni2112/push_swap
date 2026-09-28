/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andpascu <andpascu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/28 18:53:53 by andpascu          #+#    #+#             */
/*   Updated: 2026/09/28 19:04:31 by andpascu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "../Libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef struct s_config
{
	int	flag_simple;
	int	flag_medium;
	int	flag_complex;
	int	flag_adaptive;
	int	flag_bench;
}	t_config;

t_stack	*stack_new(int value);
t_stack	*stack_last(t_stack *stack);
int		stack_size(t_stack *stack);
void	stack_add_back(t_stack **stack, t_stack *new_node);
void	free_stack(t_stack **stack);
void	free_split(char **args);
void	print_error(t_stack **a, t_stack **b);
int		get_index_pos(t_stack *stack, int target_index);
int		has_duplicates(t_stack *stack);
int		is_within_int_limits(long num);
long	ft_atol(const char *str);
int		is_number(char *str);
void	parse_input(int argc, char **argv, t_stack **a, t_config *config);
int		parse_flags(char *arg, t_config *config);
void	sa(t_stack *a);
void	sb(t_stack *b);
void	ss(t_stack *a, t_stack *b);
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);
void	index_stack(t_stack *stack);
double	compute_disorder(t_stack *stack);
int		is_sorted(t_stack *stack);
int		sort_three(t_stack **a);
int		sort_small(t_stack **a, t_stack **b);
int		strategy_simple(t_stack **a, t_stack **b);
int		strategy_medium(t_stack **a, t_stack **b);
int		strategy_complex(t_stack **a, t_stack **b);
int		strategy_adaptive(t_stack **a, t_stack **b);
void	print_benchmark(t_config *config, double disorder, int total_ops);

#endif