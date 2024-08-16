/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:10 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/16 00:05:06 by mfontser         ###   ########.fr       */
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
	init_quote_values(data);
	while (s[i])
	{
		if ((s[i] == '"' && data->qdata.miniquotes == 0) || (s[i] == '\'' && data->qdata.quotes == 0))
			account_quotes (s[i], data);
		if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0 && s[i] != del && (s[i + 1] == del || s[i + 1] == '\0'))
			words ++;
		i++;
	}
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
		if ((s[i] == '"' && data->qdata.miniquotes == 0) || (s[i] == '\'' && data->qdata.quotes == 0))
			account_quotes (s[i], data);
		if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			while (s[i] == del)
				i++;
		}
		start = i;
		if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			while (s[i] != del && s[i] != '\0')
				i++;
			res[word] = ft_substr(s, start, i - start);
			printf("     Palabra %d: |%s|\n", word + 1, res[word]);
		}
		else if (data->qdata.quotes == 1)
		{
			i++; //porque ya estoy en las comillas, y sino no entro
			while (s[i] != '"')
				i++;
			i++; // sino en la siguiente iteracion estare aun en la comilla y la cogere como palabra
			res[word] = ft_substr(s, start, i - start);
			printf("     Palabra %d: |%s|\n", word + 1, res[word]);
		}

		else if (data->qdata.miniquotes == 1)
		{
			i++;
			while (s[i] != '\'')
				i++;
			i++;
			res[word] = ft_substr(s, start, i - start);
			printf("     Palabra %d: |%s|\n", word + 1, res[word]);
		}
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

	
	words = token_num_words (s, del, data);
	printf("  >> Split:\n");
	printf("     Numero de palabras: |%d|\n", words);
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = matrix_token_words(res, s, del, data);
	return (res);
}