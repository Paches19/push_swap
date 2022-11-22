/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:43:51 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 13:45:29 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	swap(long int ****stack)
{
	long int	temp;

	temp = stack[0][0][0][0];
	stack[0][0][0][0] = stack[0][0][0][1];
	stack[0][0][0][1] = temp;
	write(1, "sa\n", 3);
	return (1);
}

int	p_a(long int ****stack_a, long int ***stack_b)
{
	stack_a[0][0][0][stack_len(&stack_b) - 1] = stack_b[0][0][0];
	del_stack_b(stack_b, 0);
	write(1, "pa\n", 3);
	return (1);
}

int	push_b(long int ****stack_a, long int ***stack_b)
{
	stack_b[0][0][stack_len(&stack_b)] = stack_a[0][0][0][0];
	del_stack(stack_a, 0);
	write(1, "pb\n", 3);
	return (1);
}

int	rotate_stack(long int ****stack)
{
	const int	len_stack = stack_len(stack);
	long int	ini;
	int			i;

	ini = stack[0][0][0][0];
	i = -1;
	while (++i < len_stack && stack[0][0][0][i] <= INT_MAX)
		stack[0][0][0][i] = stack[0][0][0][i + 1];
	stack[0][0][0][len_stack - 1] = ini;
	write(1, "ra\n", 3);
	return (1);
}

int	rotate_stack_b(long int ***stack)
{
	const int	len_stack = stack_len(&stack);
	long int	ini;
	int			i;

	ini = stack[0][0][0];
	i = -1;
	while (++i < len_stack && stack[0][0][i] <= INT_MAX)
		stack[0][0][i] = stack[0][0][i + 1];
	stack[0][0][len_stack - 1] = ini;
	write(1, "rb\n", 3);
	return (1);
}
