# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/08 12:03:07 by adpachec          #+#    #+#              #
#    Updated: 2022/11/22 14:06:51 by adpachec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= push_swap

SRCS			= push_swap.c check_argv.c check_stacks.c get_num_stacks.c \
					operations_1.c operations_2.c push_swap_utils.c \
					push_swap_utils_2.c

OBJS			= $(SRCS:.c=.o)

CC				= gcc

CFLAGS			= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)
		$(CC) $(CFLAGS) -c $(SRCS)

clean:
		rm -rf $(OBJS)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all re clean fclean