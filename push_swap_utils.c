/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:46:40 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 13:47:22 by adpachec         ###   ########.fr       */
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

void	error_exit(void)
{
	write(2, "Error\n", 6);
	exit(-1);
}
