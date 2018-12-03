/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlucas-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 21:42:42 by rlucas-d          #+#    #+#             */
/*   Updated: 2018/12/02 17:58:10 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	ft_stop(char **str)
{
	int a;

	a = 0;
	while (str[a])
		free(str[a++]);
	free(str);
	return (0);
}

static int	ft_word(char const *str, char c)
{
	int count;
	int a;

	a = 0;
	count = 0;
	while (str[a])
	{
		if (str[a] != c)
		{
			count++;
			while (str[a] != c && str[a])
				a++;
		}
		else
			a++;
	}
	return (count);
}

static char	*ft_cast(char const *s, char c)
{
	int		a;
	char	*word;

	a = 0;
	if (!(word = ft_memalloc((ft_count_letter(s, c) + 1))))
		return (NULL);
	while (s[a] != c && s[a])
	{
		word[a] = s[a];
		a++;
	}
	word[a] = '\0';
	return (word);
}

int		ft_strsplit_v2(char const *s, char c, char ***new)
{
	int		a;
	int		nb_word;

	nb_word = ft_word(s, c);
	a = 0;
	if (!s || !(*new = ft_memalloc((ft_word(s, c) + 1))))
		return (0);
	while (s[a])
	{
		while (s[a] == c && s[a])
			a++;
		if (s[a] != c && s[a])
		{
			if (!(ft_cast(s + a, c)))
				return (ft_stop(*new) && (int)(new = NULL) && 0);
			**new = ft_cast(s + a, c);
			(*new)++;
			while (s[a] != c && s[a])
				a++;
		}
	}
	**new = NULL;
	*new -= nb_word;
	return (nb_word);
}
