/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_argv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adpachec <adpachec@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 11:12:55 by adpachec          #+#    #+#             */
/*   Updated: 2023/01/25 12:11:21 by adpachec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t	ft_words(const char *s, char c)
{
	size_t	i;
	size_t	words;

	words = 0;
	if (s[0] == '\0')
		return (0);
	i = 0;
	if (s[0] != c)
	{
		++words;
		++i;
	}
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			++words;
		++i;
	}
	return (words);
}

static void	ft_free_res(char **res)
{
	size_t	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		res[i] = NULL;
		++i;
	}
	free(res);
}

static void	ft_init_matrix(const char *s, char c, char **res, size_t words)
{
	size_t	j;
	size_t	temp;

	j = 0;
	while (*s != '\0' && j <= words)
	{
		temp = 0;
		while (*s == c)
			++s;
		while (*s != c && *s != '\0')
			++s;
		if (temp > 0)
		{
			res[j] = ft_substr(s - temp, 0, temp);
			if (!res[j++])
			{
				ft_free_res(res);
				return ;
			}
		}
	}
	res[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	size_t	words;
	char	**res;

	if (!s)
		return (NULL);
	words = ft_words(s, c);
	res = (char **) ft_calloc(sizeof(char *), (words + 1));
	if (!res)
		return (NULL);
	ft_init_matrix(s, c, res, words);
	if (!res)
		return (NULL);
	return (res);
}
