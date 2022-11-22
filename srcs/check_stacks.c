/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_stacks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:39:08 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 13:39:42 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

bool	check_end_sort_a(long int ***stack)
{
	int	i;

	i = -1;
	while (stack[0][0][++i] <= INT_MAX)
	{
		if (stack[0][0][i] > stack[0][0][i + 1])
			return (false);
	}
	return (true);
}

bool	check_end_group(long int ***stack, int group_len)
{
	int	i;

	i = -1;
	while (stack[0][0][++i] <= INT_MAX)
	{
		if (stack[0][0][i] <= group_len)
			return (false);
	}
	return (true);
}

bool	check_num_push(long int ***stack, int num)
{
	int	i;

	i = -1;
	while (stack[0][0][++i] <= INT_MAX)
	{
		if (stack[0][0][i] == num)
			return (false);
	}
	return (true);
}
