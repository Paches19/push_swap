/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:59 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/10 10:57:42 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "stdio.h"
#include <limits.h>


void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *) s;
	i = -1;
	while (++i < n && n > 0)
		ptr[i] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*ptr;
	const size_t	len = count * size;

	if (!count)
		return (malloc(0));
	if (len / count != size)
		return (NULL);
	ptr = (void *) malloc(len);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, len);
	return (ptr);
}

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

long int	ft_atoi(char *str)
{
	int			sign;
	long int	result;

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

int	check_arg_order(int argc, long int **stack)
{
	int	i;
	
	i = -1;
	while (++i < argc - 2)
	{
		if (stack[0][i] > stack[0][i + 1])
			return (-1);
	}
	exit (1);
}

long int	*check_duplicate_order(int argc, char **argv)
{
	int			i;
	int			j;
	long int	*stack;

	stack = (long int *)ft_calloc(sizeof(long int), argc);
	if (!stack)
		error_exit();
	stack[argc - 1] = (long int) INT_MAX + 1;
	i = 0;
	while (++i < argc)
	{
		stack[i - 1] = ft_atoi(argv[i]);
		j = 0;
		while (j < i - 1)
		{
			if (stack[j++] == stack[i - 1])
				error_exit();
		}
	}
	check_arg_order(argc, &stack);
	return (stack);
}

long int	*check_argv(int argc, char **argv)
{
	long int	*stack;
	
	check_num(argc, argv);
	stack = check_duplicate_order(argc, argv);
	return (stack);
}

void del_stack(long int ****stack, int pos)
{
	while(stack[0][0][0][pos] <= INT_MAX)
	{
		stack[0][0][0][pos] = stack[0][0][0][pos + 1];
		++pos;
	}
}

int	stack_len(long int ****stack)
{
	int	len;
	
	len = 0;
	while (stack[0][0][0][len] <= INT_MAX)
		++len;
	return (len);
}

int	get_min_stack(long int ***stack, int *min_pos)
{
	int	min;
	int	i;

	min = INT_MAX;
	i = -1;
	while (stack[0][0][++i] <= INT_MAX)
	{
		if (stack[0][0][i] < min)
		{
			min = stack[0][0][i];
			*min_pos = i;
		}
	}
	return (min);
}

int	reverse_rotate_stack (long int ****stack)
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

int	rotate_stack (long int ****stack)
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

int	swap(long int ****stack)
{
	long int	temp;

	temp = stack[0][0][0][0];
	stack[0][0][0][0] = stack[0][0][0][1];
	stack[0][0][0][1] = temp;
	write(1, "sa\n", 3);
	return (1);
}

int	push_b(long int ****stack_a, long int ***stack_b, int *i)
{
	stack_b[0][0][++*i] = stack_a[0][0][0][0];
	del_stack(stack_a, 0);
	write(1, "pb\n", 3);
	return (1);
}

void	sort_stack_a(long int ***stack_a, long int **stack_b, int *num_op)
{
	int	min;
	int	i;
	int	st_len;
	int	min_pos;

	i = -1;
	st_len = stack_len(&stack_a);
	while (st_len > 0)
	{
		min = get_min_stack(stack_a, &min_pos);
		if (stack_a[0][0][1] < stack_a[0][0][0])
			*num_op += swap(&stack_a);
		if (stack_a[0][0][0] == min)
			*num_op += push_b(&stack_a, &stack_b, &i);
		else
		{
			if (stack_a[0][0][0] <= INT_MAX)
			{
				if (min_pos <= st_len / 2)
					*num_op += rotate_stack(&stack_a);
				else
					*num_op += reverse_rotate_stack(&stack_a);
			}
		}
		st_len = stack_len(&stack_a);
	}
}

void	push_b_to_a(long int ***stack_a, long int **stack_b, int *num_op)
{
	int	i;
	int	j;
	long int	***s;
	long int	****stack;

	s = &stack_b;
	stack = &s;
	i = stack_len(stack);
	
	j = -1;
	while (--i >= 0)
	{
		stack_a[0][0][++j] = stack_b[0][i];
		write(1, "pb\n", 3);
		++*num_op;
	}
}

void	push_swap(int argc, long int **stack_a)
{
	long int	*stack_b;
	int			i;
	int			num_op;

	num_op = 0;
	stack_b = (long int *)ft_calloc(argc, sizeof(long int));
	if (!stack_b)
		error_exit();
	stack_b[argc - 1] = (long int) INT_MAX + 1;
	sort_stack_a(&(stack_a), &stack_b, &num_op);
	push_b_to_a(&(stack_a), &stack_b, &num_op);
	free(stack_b);
	i = -1;
	while (stack_a[0][++i] <= INT_MAX)
		printf("\nsapos: %ld", stack_a[0][i]);
	printf("\nnum_op: %d", num_op);
	printf("\n");
	return ;
}

int	main(int argc, char **argv)
{
	long int	*stack_a;

	if (argc <= 1)
		exit (-1);
	else if (argc == 2)
		return (0);
	else
		stack_a = check_argv(argc, argv);
	push_swap(argc, &stack_a);
	free(stack_a);
	return (0);
}
