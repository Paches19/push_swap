/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:59 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/04 13:01:55 by adpachec         ###   ########.fr       */
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

void	check_arg_order(int argc, long int **stack)
{
	int	i;
	int	j;
	
	i = -1;
	while (++i < argc - 2)
	{
		j = i + 1;
		if (stack[0][i] > stack[0][j++])
			return ;
	}
	printf("\nordenado\n");
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

void	sort_positive(long int ***stack_a, long int **stack_b)
{
	int	i;
	int	j;
	int	pos;
	int	unit;

	i = 0;
	j = 0;
	pos = 1;
	unit = 0;
	while (stack_a[0][0][i] <= INT_MAX)
	{
		printf("\nsa: %ld", stack_a[0][0][i]);
		if(stack_a[0][0][i] > 0)
		{
			printf("\ndiv: %ld", stack_a[0][0][i] / (10 * pos));
			if(stack_a[0][0][i] / (10 * pos) == unit)
			{
				stack_b[0][j] = stack_a[0][0][i];
				printf("\nsb: %ld", stack_b[0][j]);
				del_stack(&(stack_a), i);
			}
		}
		++pos;
		++unit;
		++i;
	}
}

void	push_swap(int argc, char **argv, long int **stack_a)
{
	long int	*stack_b;

	stack_b = (long int *)ft_calloc(argc, sizeof(long int));
	if (!stack_b)
		error_exit();
	stack_b[argc - 1] = (long int) INT_MAX + 1;
	if (argv)
		sort_positive(&(stack_a), &stack_b);
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