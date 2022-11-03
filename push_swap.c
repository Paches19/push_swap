/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:59 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/03 13:36:49 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"
# include <limits.h>
/*
int	get_min(t_list *lst, int min)
{
	if (lst->content < min)
		return(lst->content);
	return (min);
}

int	ft_lstiter(t_list *lst, int (*f)(void *, int min))
{
	int	min;

	min = 2147483647;
	if (!lst || !f)
		return (-1);
	while (lst)
	{
		min = f(lst->content, min);
		lst = lst->next;
	}
	return (min);
}

bool	check_min_bottom(t_list *stack_a, int min)
{
	while (stack_a)
	{
		
	}
	if (stack_a->content == min)
		return (true);
	return (false);
}

void	push_swap(t_list *stack_a)
{
	t_list		*stack_b;
	char		*sol;
	const int	stack_len = ft_lstsize(&stack_a);
	int			num_op;
	int			min;
	int			i;
	int			index;

	min = ft_lstiter(&stack_a, get_min(&stack_a, min));		
}
*/
void	error_exit(void)
{
	write(1, "Error\n", 6);
	exit(-1);
}

int	ft_isdigit(int c)
{
	if (c < 48 || c > 57)
		return (0);
	return (1);
}

int	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		++str;
	}
	result = 0;
	while (*str != '\0')
	{
		result = (result * 10) + (*str - '0') * sign;
		if (result > INT_MAX)
			error_exit();
		else if (result < INT_MIN)
			error_exit();
		++str;
	}
	return (result);
}

void	check_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if ((argv[i][0] == '-' && ft_isdigit(argv[i][j + 1])) || ft_isdigit(argv[i][j]))
				++j;
			else
				error_exit();
		}
	}
}

void	check_arg_order(int argc, int *stack)
{
	int	i;
	int	j;

	i = -1;
	while (++i < argc - 2)
	{
		j = i + 1;
		while (j < argc - 1)
		{
			if (stack[i] > stack[j++])
				return ;
		}
	}
	exit (1);
}

void	check_duplicate_order(int argc, char **argv)
{
	int	*stack;
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	stack = (int *)malloc(sizeof(int) * argc);
	while (++i < argc)
	{
		stack[j] = ft_atoi(argv[i]);
		k = 0;
		while (k < j)
		{
			if (stack[k++] == stack[j])
				error_exit();
		}
		++j;
	}
	check_arg_order(argc, stack);
}

void	check_argv(int argc, char **argv)
{
	check_num(argc, argv);
	check_duplicate_order(argc, argv);
}

int	main(int argc, char **argv)
{
	if (argc <= 1)
		exit (-1);
	else if (argc == 2)
		return (0);
	else
		check_argv(argc, argv);
	printf("\nokey\n");
	return (0);
}