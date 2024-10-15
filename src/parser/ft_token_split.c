/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:10 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/15 15:37:25 by yanaranj         ###   ########.fr       */
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

//Cosas a probar en terminal para parseo:
//|a"asd "   asas   "asdf "s|
// "       asdfa   " asfasdf as"asdf  " asdf"   asdf" asdf a "asdfdf"as  asf"asdfas"as 



static char	**matrix_token_words(char **res, const char *s, char del, t_general *data)
{
	int	i;
	int	start;
	int	word;
	int	j;
	int stopper;

	i = 0;
	j = -1;
	word = 0;
	stopper = token_num_words(s, del, data); 
	while (++j < stopper) // no puedo poner de condicion la funcion, porque sino la llama cada vez y me resetea las quotes a 0. Si saco lo de las quotes de esa funcion, al llamarla igualmente estaria sesgado y me daria mal el recuento de palabras.
	{
		if ((s[i] == '"' && data->qdata.miniquotes == 0) || (s[i] == '\'' && data->qdata.quotes == 0))
			account_quotes (s[i], data);
		if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			while (s[i] == del)
				i++;
			account_quotes (s[i], data);
		}
		// printf ("valor de quotes %d\n", data->qdata.quotes);
		// printf ("valor de miniquotes %d\n", data->qdata.miniquotes);
		start = i;
		if (data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			while (s[i] != del && s[i] != '\0')
			{
				// printf("\n\nevaluando la letra: |%c|\n", s[i]);
				i++;
				// printf("evaluando la letra: |%c|\n", s[i]);
				account_quotes (s[i], data);
				// printf ("valor de quotes %d\n", data->qdata.quotes);
				if (data->qdata.quotes == 1)
				{
					i++; //porque ya estoy en las comillas, y sino no entro
					while (s[i] != '"')
					{
						i++;
						// printf("Evaluando la letra: |%c|\n", s[i]);
					}
				}
				else if(data->qdata.miniquotes == 1)
				{
					i++; //porque ya estoy en las comillas, y sino no entro
					while (s[i] != '\'')
					{
						i++;
						// printf("Evaluando la letra: |%c|\n", s[i]);
					}
				}
				account_quotes (s[i], data);

			}
			res[word] = ft_substr(s, start, i - start);
		}
		else if (data->qdata.quotes == 1)
		{
			i++; //porque ya estoy en las comillas, y sino no entro
			while (s[i] != '"')
				i++;
			account_quotes (s[i], data);
			i++; // sino en la siguiente iteracion estare aun en la comilla y la cogere como palabra
			while (s[i] != '\0' && s[i] != del)
				i++;
			res[word] = ft_substr(s, start, i - start);
		}

		else if (data->qdata.miniquotes == 1)
		{
			i++;
			while (s[i] != '\'')
				i++;
			account_quotes (s[i], data);
			i++;
			while (s[i] != '\0' && s[i] != del)
				i++;
			res[word] = ft_substr(s, start, i - start);
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
	res = malloc(sizeof(char *) * (words + 1));
	if (!res)
		return (NULL);
	res = matrix_token_words(res, s, del, data);
	return (res);
}
