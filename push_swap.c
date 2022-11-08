/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:59 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/08 13:35:33 by adpachec         ###   ########.fr       */
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
	//printf("\nordenado\n");
	return (1);
}

int	check_arg_order_neg(long int **stack)
{
	int	i;

	i = 0;
	while (stack[0][i] >= 0)
		++i;
	while (stack[0][i] <= INT_MAX)
	{
		if (stack[0][i] > stack[0][i + 1])
			return (-1);
		++i;
	}
	//printf("\nordenado neg\n");
	return (1);
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

int	get_divisor(int pos)
{
	int	divisor;
	
	divisor = 10;
	while (--pos > 0)
		divisor *= 10;
	return (divisor);
}

int	extract_unit(long int stack, int divisor)
{
	int	result;

	if (stack < 0)
		stack *= (-1);
	if (stack < 10 && divisor > 10)
		return (0);
	if (stack * 10 < divisor)
		return (0);
	if (divisor == 0)
		return (0);
	result = stack % divisor;
	while (result > 10)
		result = result / 10;
	return (result);
}

int	push_a(void)
{
	//write(1, "pa\n", 3);
	return (1);
}

int	rotate_a(void)
{
	//write(1, "ra\n", 3);
	return (1);
}

int	push_b(void)
{
	//write(1, "pb\n", 3);
	return (1);
}

int	rotate_b(void)
{
	//write(1, "rb\n", 3);
	return (1);
}

int	sort_positive_a_to_b(long int ****stack_a, long int ***stack_b, int pos, int len, int *num_op)
{
	int			i;
	int			unit;
	const int	divisor = get_divisor(pos);

	unit = -1;
	while (++unit < 10)
	{
		i = -1;
		while (stack_a[0][0][0][++i] <= INT_MAX)
		{
			printf("\nsA[%d]: %ld", i, stack_a[0][0][0][i]);
			if (stack_a[0][0][0][i] >= 0 && \
			extract_unit(stack_a[0][0][0][i], divisor) == unit)
			{
				stack_b[0][0][len++] = stack_a[0][0][0][i];
				printf("\nsb[%d]: %ld", len - 1, stack_b[0][0][len - 1]);
				del_stack(stack_a, i);
				--i;
				*num_op += push_b();
			}
			else
				*num_op += rotate_a();
		}
	}
	while (stack_b[0][0][len] <= INT_MAX)
		stack_b[0][0][len++] = (long int) INT_MAX + 1;
	printf("\n\nnum_op posab: %d\n\n", *num_op);
	return (stack_len(stack_a));
}

int	sort_positive_b_to_a(long int ****stack_a, long int ***stack_b, int pos, int len, int *num_op)
{
	int			i;
	int			unit;
	const int	divisor = get_divisor(pos);

	unit = -1;
	while (++unit < 10)
	{
		i = -1;
		while (stack_b[0][0][++i] <= INT_MAX)
		{
			printf("\nsA[%d]: %ld", i, stack_a[0][0][0][i]);
			if(stack_b[0][0][i] >= 0 && \
			extract_unit(stack_b[0][0][i], divisor) == unit)
			{
				stack_a[0][0][0][len++] = stack_b[0][0][i];
				printf("\nsb[%d]: %ld", len - 1, stack_b[0][0][len - 1]);
				del_stack(&(stack_b), i);
				--i;
				*num_op += push_a();
			}
			else
				*num_op += rotate_b();
		}
	}
	while (stack_a[0][0][0][len] <= INT_MAX)
		stack_a[0][0][0][len++] = (long int) INT_MAX + 1;
	printf("\n\nnum_op posba: %d\n\n", *num_op);
	return (stack_len(&stack_b));
}

void	sort_positive(int argc, long int ***stack_a, long int **stack_b, int *num_op)
{
	int	pos;
	int	len;

	pos = 1;
	len = 0;
	while (check_arg_order(argc, *stack_a) != 1)
	{
		len = sort_positive_a_to_b(&(stack_a), &stack_b, pos, len, num_op);
		++pos;
		len = sort_positive_b_to_a(&(stack_a), &stack_b, pos, len, num_op);
		++pos;
	}
	return ;
}

int	get_max_pos(long int ***stack)
{
	int	tam;
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (stack[0][0][++i] <= INT_MAX)
	{
		if (stack[0][0][i] < 0)
		{
			if (stack[0][0][i] * (-1) > max)
				max = stack[0][0][i] * (-1);
		}
	}
	tam = 1;
	while (max > 10)
	{
		++tam;
		max = max / 10;
	}
	return (tam);
}

int	sort_negative_a_to_b(long int ****stack_a, long int ***stack_b, int pos, int len, int *num_op)
{
	int			i;
	int			unit;
	const int	divisor = get_divisor(pos);

	unit = 10;
	while (--unit > -1)
	{
		i = -1;
		while (stack_a[0][0][0][++i] <= INT_MAX)
		{
			printf("\nsA[%d]: %ld", i, stack_a[0][0][0][i]);
			if (stack_a[0][0][0][i] < 0 && \
			extract_unit(stack_a[0][0][0][i], divisor) == unit)
			{
				stack_b[0][0][len++] = stack_a[0][0][0][i];
				printf("\nsb[%d]: %ld", len - 1, stack_b[0][0][len - 1]);
				del_stack(stack_a, i);
				--i;
				*num_op += push_b();
			}
			else
				*num_op += rotate_a();
		}
	}
	while (stack_b[0][0][len] <= INT_MAX)
		stack_b[0][0][len++] = (long int) INT_MAX + 1;
	printf("\n\nnum_op negab: %d\n\n", *num_op);
	return (stack_len(stack_a));
}

int	sort_negative_b_to_a(long int ****stack_a, long int ***stack_b, int pos, int len, int *num_op)
{
	int			i;
	int			unit;
	const int	divisor = get_divisor(pos);
	
	unit = 10;
	while (--unit > -1)
	{
		i = -1;
		while (stack_b[0][0][++i] <= INT_MAX)
		{
			printf("\nsA[%d]: %ld", i, stack_a[0][0][0][i]);
			if(stack_b[0][0][i] < 0 && \
			extract_unit(stack_b[0][0][i], divisor) == unit)
			{
				stack_a[0][0][0][len++] = stack_b[0][0][i];
				printf("\nsb[%d]: %ld", len - 1, stack_b[0][0][len - 1]);
				del_stack(&(stack_b), i);
				--i;
				*num_op += push_a();
			}
			else
				*num_op += rotate_b();
		}
	}
	while (stack_a[0][0][0][len] <= INT_MAX)
		stack_a[0][0][0][len++] = (long int) INT_MAX + 1;
	printf("\n\nnum_op negba: %d\n\n", *num_op);
	return (stack_len(&stack_b));
}

void	sort_negative(long int ***stack_a, long int **stack_b, int *num_op)
{
	int	pos;
	int	len;

	pos = get_max_pos(stack_a);
	len = 0;
	len = sort_negative_a_to_b(&(stack_a), &stack_b, pos, len, num_op);
	len = sort_negative_b_to_a(&(stack_a), &stack_b, --pos, len, num_op);
	while (check_arg_order_neg(*stack_a) != 1 && pos > 1)
	{
		len = sort_negative_a_to_b(&(stack_a), &stack_b, --pos, len, num_op);
		len = sort_negative_b_to_a(&(stack_a), &stack_b, --pos, len, num_op);
	}
	return ;
}

void	push_swap(int argc, char **argv, long int **stack_a)
{
	long int	*stack_b;
	static int	num_op;

	num_op = 0;
	stack_b = (long int *)ft_calloc(argc, sizeof(long int));
	if (!stack_b)
		error_exit();
	stack_b[argc - 1] = (long int) INT_MAX + 1;
	if (argv)
	{
		sort_negative(&(stack_a), &stack_b, &num_op);
		sort_positive(argc, &(stack_a), &stack_b, &num_op);
	}
	printf("\nop: %d\n", num_op);
	free(stack_b);
	//i = -1;
	//while (stack_a[0][++i] <= INT_MAX)
	//	printf("\nsapos: %ld", stack_a[0][i]);
	//printf("\n");
	//printf ("\nfin\n");
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
	//printf("\nokey\n");
	push_swap(argc, argv, &stack_a);
	free(stack_a);
	return (0);
}