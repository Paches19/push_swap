/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:47:42 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 13:48:28 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	stack_len(long int ****stack)
{
	int	len;

	len = 0;
	while (stack[0][0][0][len] <= INT_MAX)
		++len;
	return (len);
}

int	stack_len_b(long int ***stack)
{
	int	len;

	len = 0;
	while (stack[0][0][len] <= INT_MAX)
		++len;
	return (len);
}

void	reverse_array_b(long int **stack_b)
{
	int			i;
	int			j;
	long int	temp;

	i = 0;
	j = stack_len_b(&stack_b) - 1;
	while (i < j)
	{
		temp = stack_b[0][i];
		stack_b[0][i++] = stack_b[0][j];
		stack_b[0][j--] = temp;
	}
}

void	min_to_parse_stack(long int ***stack_a, long int **parse_stack, \
int min, int i)
{
	int	j;

	j = 0;
	while (stack_a[0][0][j] != min)
		++j;
	parse_stack[0][j] = i;
	stack_a[0][0][j] = (long int) INT_MAX + 1;
}

long int	*map_stack_a(int argc, long int **stack_a)
{
	long int	*parse_stack;
	int			min;
	int			min_pos;
	int			i;

	parse_stack = (long int *)ft_calloc(argc, sizeof(long int));
	parse_stack[argc - 1] = (long int) INT_MAX + 2;
	i = 0;
	min_pos = 0;
	while (i < argc - 1)
	{
		min = get_min_stack(&stack_a, &min_pos);
		min_to_parse_stack(&stack_a, &parse_stack, min, i);
		++i;
	}
	free (*stack_a);
	return (parse_stack);
}
