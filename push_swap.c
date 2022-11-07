/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:59 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/07 13:49:56 by adpachec         ###   ########.fr       */
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
	int	j;
	
	i = -1;
	while (++i < argc - 2)
	{
		j = i + 1;
		if (stack[0][i] > stack[0][j++])
			return (-1);
	}
	printf("\nordenado\n");
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


int	extract_unit(long int stack, int divisor)
{
	int	result;

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

int	sort_positive_a_to_b(long int ****stack_a, long int ***stack_b, int pos, int len)
{
	int	i;
	int	unit;
	int	divisor;

	divisor = 10;
	while (--pos > 0)
		divisor *= 10;
	unit = -1;
	while (++unit < 10)
	{
		i = -1;
		while (stack_a[0][0][0][++i] <= INT_MAX)
		{
			if (stack_a[0][0][0][i] >= 0 && \
			extract_unit(stack_a[0][0][0][i], divisor) == unit)
			{
				stack_b[0][0][len++] = stack_a[0][0][0][i];
				del_stack(stack_a, i);
				--i;
			}
		}
	}
	while (stack_b[0][0][len] <= INT_MAX)
		stack_b[0][0][len++] = (long int) INT_MAX + 1;
	return (stack_len(stack_a));
}

int	sort_positive_b_to_a(long int ****stack_a, long int ***stack_b, int pos, int len)
{
	int	i;
	int	unit;
	int	divisor;

	divisor = 10;
	while (--pos > 0)
		divisor *= 10;
	unit = -1;
	while (++unit < 10)
	{
		i = -1;
		while (stack_b[0][0][++i] <= INT_MAX)
		{
			if(stack_b[0][0][i] >= 0 && \
			extract_unit(stack_b[0][0][i], divisor) == unit)
			{
				stack_a[0][0][0][len++] = stack_b[0][0][i];
				del_stack(&(stack_b), i);
				--i;
			}
		}
	}
	while (stack_a[0][0][0][len] <= INT_MAX)
		stack_a[0][0][0][len++] = (long int) INT_MAX + 1;
	return (stack_len(&stack_b));
}

void	sort_positive(int argc, long int ***stack_a, long int **stack_b)
{
	int	pos;
	int	len;
	int	i;

	pos = 1;
	len = 0;
	while (check_arg_order(argc, *stack_a) != 1)
	{
		len = sort_positive_a_to_b(&(stack_a), &stack_b, pos, len);
		++pos;
		len = sort_positive_b_to_a(&(stack_a), &stack_b, pos, len);
		++pos;
	}
	i = -1;
	while (stack_a[0][0][++i] <= INT_MAX)
	{
		printf("\nsa2: %ld", stack_a[0][0][i]);
	}
	printf("\n");
	i = -1;
	while (stack_b[0][++i] <= INT_MAX)
	{
		printf("\nsb2: %ld", stack_b[0][i]);
	}
	printf("\n");
	exit(1);
}

void	push_swap(int argc, char **argv, long int **stack_a)
{
	long int	*stack_b;

	stack_b = (long int *)ft_calloc(argc, sizeof(long int));
	if (!stack_b)
		error_exit();
	stack_b[argc - 1] = (long int) INT_MAX + 1;
	if (argv)
		sort_positive(argc, &(stack_a), &stack_b);
	free(stack_b);
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
	printf("\nokey\n");
	push_swap(argc, argv, &stack_a);
	free(stack_a);
	return (0);
}