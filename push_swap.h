/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:51:30 by adpachec          #+#    #+#             */
/*   Updated: 2022/11/22 14:04:52 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <limits.h>

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isdigit(int c);
long int	ft_atoi(char *str);
void		error_exit(void);
int			stack_len(long int ****stack);
int			stack_len_b(long int ***stack);
void		reverse_array_b(long int **stack_b);
void		min_to_parse_stack(long int ***stack_a, long int **parse_stack, \
int min, int i);
long int	*map_stack_a(int argc, long int **stack_a);
void		push_to_a(long int ***stack_a, long int **stack_b);
int			reverse_rotate_stack(long int ****stack);
int			reverse_rotate_stack_b(long int ***stack);
void		del_stack(long int ****stack, int pos);
void		del_stack_b(long int ***stack, int pos);
int			swap(long int ****stack);
int			p_a(long int ****stack_a, long int ***stack_b);
int			push_b(long int ****stack_a, long int ***stack_b);
int			rotate_stack(long int ****stack);
int			rotate_stack_b(long int ***stack);
bool		check_end_sort_a(long int ***stack);
bool		check_end_group(long int ***stack, int group_len);
bool		check_num_push(long int ***stack, int num);
long int	*check_argv(int argc, char **argv);
long int	*check_duplicate_order(int argc, char **argv);
int			check_arg_order(int argc, long int **stack);
void		check_num(int argc, char **argv);
int			get_min_stack(long int ***stack, int *min_pos);
int			num_to_push(long int ***stack, int *num_pos, int group_len, \
int argc);
int			decide_group_len(int argc);
int			get_next_group_len(int argc, int group_len);
int			get_max_stack(long int ***stack, int *max_pos);

#endif