/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:45:35 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 13:48:49 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_to_a(long int ***stack_a, long int **stack_b)
{
	int	max;
	int	max_pos;
	int	st_len;

	max_pos = 0;
	st_len = 0;
	while (stack_len_b(&stack_b))
	{
		max = get_max_stack(&stack_b, &max_pos);
		if (stack_b[0][0] == max)
			p_a(&stack_a, &stack_b);
		else
		{
			if (max_pos <= st_len / 2 && stack_b[0][1] <= INT_MAX)
				rotate_stack_b(&stack_b);
			else if (stack_b[0][1] <= INT_MAX)
				reverse_rotate_stack_b(&stack_b);
		}
		st_len = stack_len_b(&stack_b);
	}
}

int	reverse_rotate_stack(long int ****stack)
{
	const int	len_stack = stack_len(stack);
	long int	end;
	int			i;

	end = stack[0][0][0][len_stack - 1];
	i = len_stack;
	while (--i > 0 && stack[0][0][0][i] <= INT_MAX)
		stack[0][0][0][i] = stack[0][0][0][i - 1];
	stack[0][0][0][0] = end;
	write(1, "rra\n", 4);
	return (1);
}

int	reverse_rotate_stack_b(long int ***stack)
{
	const int	len_stack = stack_len(&stack);
	long int	end;
	int			i;

	end = stack[0][0][len_stack - 1];
	i = len_stack;
	while (--i > 0 && stack[0][0][i] <= INT_MAX)
		stack[0][0][i] = stack[0][0][i - 1];
	stack[0][0][0] = end;
	write(1, "rrb\n", 4);
	return (1);
}

void	del_stack(long int ****stack, int pos)
{
	while (stack[0][0][0][pos] <= INT_MAX)
	{
		stack[0][0][0][pos] = stack[0][0][0][pos + 1];
		++pos;
	}
}

void	del_stack_b(long int ***stack, int pos)
{
	while (stack[0][0][pos] <= INT_MAX)
	{
		stack[0][0][pos] = stack[0][0][pos + 1];
		++pos;
	}
}
