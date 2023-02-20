/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:59 by adpachec          #+#    #+#             */
/*   Updated: 2023/02/20 11:08:30 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	groups_to_b(int argc, long int ***stack_a, long int **stack_b)
{
	int		num;
	int		num_pos;
	int		group_len;

	group_len = 0;
	while (!check_end_sort_a(stack_a))
	{
		group_len = get_next_group_len(argc, group_len);
		while (!check_end_group(stack_a, group_len))
		{
			num = num_to_push(stack_a, &num_pos, group_len, argc);
			while (!check_num_push(stack_a, num))
			{
				if (stack_a[0][0][0] <= group_len)
					push_b(&stack_a, &stack_b);
				else if (stack_a[0][0][1] <= INT_MAX)
				{
					if (num_pos <= stack_len(&stack_a) / 2)
						rotate_stack(&stack_a);
					else
						reverse_rotate_stack(&stack_a);
				}
			}
		}
	}
}

static void	sort_five(long int ***stack_a, long int **stack_b)
{
	int	min;
	int	min_pos;
	int	st_len;

	st_len = 5;
	while (st_len > 3)
	{
		min = get_min_stack(stack_a, &min_pos);
		if (stack_a[0][0][0] == min)
			push_b(&stack_a, &stack_b);
		else if (stack_a[0][0][1] <= INT_MAX)
		{
			if (min_pos <= st_len / 2)
				rotate_stack(&stack_a);
			else
				reverse_rotate_stack(&stack_a);
		}
		st_len = stack_len(&stack_a);
	}
}

static void	sort_short(long int ***stack_a)
{
	int	max_pos;
	int	max;

	while (!check_end_sort_a(stack_a))
	{
		max = get_max_stack(stack_a, &max_pos);
		if (stack_a[0][0][0] == max)
			rotate_stack(&stack_a);
		else
			swap(&stack_a);
	}
}

static void	push_swap(int argc, long int **stack_a)
{
	long int	*stack_b;
	int			i;

	argc = stack_len_b(&stack_a) + 1;
	stack_b = (long int *)ft_calloc(argc, sizeof(long int));
	if (!stack_b)
		error_exit();
	stack_b[argc - 1] = (long int) INT_MAX + 2;
	i = -1;
	while (stack_b[++i] <= INT_MAX)
		stack_b[i] = (long int) INT_MAX + 2;
	stack_a[0] = map_stack_a(argc, stack_a);
	if (argc <= 4)
		sort_short(&stack_a);
	else if (argc <= 6)
	{
		sort_five(&stack_a, &stack_b);
		sort_short(&stack_a);
	}
	else
		groups_to_b(argc, &stack_a, &stack_b);
	reverse_array_b(&stack_b);
	push_to_a(&stack_a, &stack_b);
	free(stack_b);
	return ;
}

int	main(int argc, char **argv)
{
	long int	*stack_a;

	if (argc <= 1)
		exit (-1);
	else if (argc == 2)
		stack_a = check_one_argv(argc, argv);
	else
		stack_a = check_argv(argc, argv);
	push_swap(argc, &stack_a);
	free(stack_a);
	return (0);
}
