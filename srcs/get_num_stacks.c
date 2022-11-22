/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:40:30 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 16:17:08 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	get_min_stack(long int ***stack, int *min_pos)
{
	int	min;
	int	i;

	min = INT_MAX;
	i = -1;
	while (stack[0][0][++i] <= (long int) INT_MAX + 1)
	{
		if (stack[0][0][i] < min)
		{
			min = stack[0][0][i];
			*min_pos = i;
		}
	}
	return (min);
}

int	num_to_push(long int ***stack, int *num_pos, int group_len, int argc)
{
	int	num;
	int	i;

	num = INT_MAX;
	*num_pos = 0;
	i = -1;
	while (stack[0][0][++i] <= INT_MAX)
	{
		if (stack[0][0][i] <= group_len)
		{
			num = stack[0][0][i];
			*num_pos = i;
		}
	}
	i = stack_len(&stack);
	while (stack[0][0][--i] <= INT_MAX)
	{
		if (stack[0][0][i] <= group_len && stack[0][0][i] < num && \
		argc - 1 - i < *num_pos)
		{
			num = stack[0][0][i];
			*num_pos = i;
		}
	}
	return (num);
}

int	get_next_group_len(int argc, int group_len)
{
	if (argc - 1 <= 200)
		group_len += (argc - 1) / 6;
	else
		group_len += (argc - 1) / 12;
	return (group_len);
}

int	get_max_stack(long int ***stack, int *max_pos)
{
	int	max;
	int	i;

	max = INT_MIN;
	i = -1;
	while (stack[0][0][++i] <= (long int) INT_MAX + 1)
	{
		if (stack[0][0][i] > max)
		{
			max = stack[0][0][i];
			*max_pos = i;
		}
	}
	return (max);
}
