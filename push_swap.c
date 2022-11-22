/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:37:59 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 13:37:20 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	write(2, "Error\n", 6);
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
	exit (0);
}

long int	*check_duplicate_order(int argc, char **argv)
{
	int			i;
	int			j;
	long int	*stack;

	stack = (long int *)ft_calloc(sizeof(long int), argc);
	if (!stack)
		error_exit();
	stack[argc - 1] = (long int) INT_MAX + 2;
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
	while (stack[0][0][0][pos] <= INT_MAX)
	{
		stack[0][0][0][pos] = stack[0][0][0][pos + 1];
		++pos;
	}
}

void del_stack_b(long int ***stack, int pos)
{
	while (stack[0][0][pos] <= INT_MAX)
	{
		stack[0][0][pos] = stack[0][0][pos + 1];
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

int	stack_len_b(long int ***stack)
{
	int	len;

	len = 0;
	while (stack[0][0][len] <= INT_MAX)
		++len;
	return (len);
}

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

//puede q borrar
int	swap(long int ****stack)
{
	long int	temp;

	temp = stack[0][0][0][0];
	stack[0][0][0][0] = stack[0][0][0][1];
	stack[0][0][0][1] = temp;
	write(1, "sa\n", 3);
	return (1);
}
//puede q borrar
int	swap_b(long int ***stack)
{
	long int	temp;

	temp = stack[0][0][0];
	stack[0][0][0] = stack[0][0][1];
	stack[0][0][1] = temp;
	write(1, "sb\n", 3);
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

int	decide_group_len(int argc)
{
	int	group_len;

	if (argc - 1 <= 5)
		group_len = 1;
	else if (argc - 1 <= 200)
		group_len = (argc - 1) / 4;
	else
		group_len = (argc - 1) / 8;
	return (group_len);
}

int	get_next_group_len(int argc, int group_len)
{
	if (argc - 1 <= 200)
		group_len += (argc - 1) / 5;
	else
		group_len += (argc - 1) / 10;
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

void	groups_to_b(int argc, long int ***stack_a, long int **stack_b)
{
	int		num;
	int		num_pos;
	int		group_len;

	group_len = 0;
	while (!check_end_sort_a(stack_a))
	{
		group_len = get_next_group_len(argc, group_len);
		while (!check_end_group(stack_a, group_len))
		{
			num = num_to_push(stack_a, &num_pos, group_len, argc);
			while (!check_num_push(stack_a, num))
			{
				if (stack_a[0][0][0] <= group_len)
					push_b(&stack_a, &stack_b);
				else if (stack_a[0][0][1] <= INT_MAX)
				{
					if (num_pos <= stack_len(&stack_a) / 2)
						rotate_stack(&stack_a);
					else
						reverse_rotate_stack(&stack_a);
				}
			}
		}
	}
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

void	sort_five(long int ***stack_a, long int **stack_b)
{
	int	min;
	int	min_pos;
	int	st_len;

	st_len = 5;
	while (st_len > 3)
	{
		min = get_min_stack(stack_a, &min_pos);
		if (stack_a[0][0][0] == min)
			push_b(&stack_a, &stack_b);
		else if (stack_a[0][0][1] <= INT_MAX)
		{
			if (min_pos <= st_len / 2)
				rotate_stack(&stack_a);
			else
				reverse_rotate_stack(&stack_a);
		}
		st_len = stack_len(&stack_a);
	}
}

void	sort_short(long int ***stack_a)
{
	int	max_pos;
	int	max;

	while (!check_end_sort_a(stack_a))
	{
		max = get_max_stack(stack_a, &max_pos);
		if (stack_a[0][0][0] == max)
			rotate_stack(&stack_a);
		else
			swap(&stack_a);
	}
}

void	push_swap(int argc, long int **stack_a)
{
	long int	*stack_b;
	int			i;

	stack_b = (long int *)ft_calloc(argc, sizeof(long int));
	if (!stack_b)
		error_exit();
	stack_b[argc - 1] = (long int) INT_MAX + 2;
	i = -1;
	while (stack_b[++i] <= INT_MAX)
		stack_b[i] = (long int) INT_MAX + 2;
	stack_a[0] = map_stack_a(argc, stack_a);
	if (argc <= 4)
		sort_short(&stack_a);
	else if (argc <= 6)
	{
		sort_five(&stack_a, &stack_b);
		sort_short(&stack_a);
	}
	else
		groups_to_b(argc, &stack_a, &stack_b);
	reverse_array_b(&stack_b);
	push_to_a(&stack_a, &stack_b);
	free(stack_b);
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
