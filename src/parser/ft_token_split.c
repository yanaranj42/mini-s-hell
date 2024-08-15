/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:10 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/15 21:26:53 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	free_token_matrix(char **res, int num_col)
{
	while (num_col)
	{
		free(res[num_col - 1]);
		num_col--;
	}
	free(res);
}

static int	token_num_words(const char *s, char del, t_general *data)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((s[i] == '"' && data->qdata.miniquotes == 0) || (s[i] == '\'' && data->qdata.quotes == 0))
			account_quotes (s[i], data);
		if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0 && s[i] != del && (s[i + 1] == del || s[i + 1] == '\0'))
			words ++;
		i++;
	}
	printf("numero de palabras: |%d|\n", words);
	return (words);
}

static char	**matrix_token_words(char **res, const char *s, char del, t_general *data)
{
	int	i;
	int	start;
	int	word;
	int	j;

	i = 0;
	j = -1;
	word = 0;
	while (++j < token_num_words(s, del, data))
	{
		while (s[i] == del)
			i++;
		start = i;
		while (s[i] != del && s[i] != '\0')
			i++;
		res[word] = ft_substr(s, start, i - start);
		if (!res[word])
		{
			free_token_matrix(res, word);
			return (NULL);
		}
		word++;
	}
	res[word] = NULL;
	return (res);
}

char	**ft_token_split(char const *s, char del, t_general *data)
{
	int		words;
	char	**res;

	init_quote_values(data);
	words = token_num_words (s, del, data);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = matrix_token_words(res, s, del, data);
	return (res);
}