/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 21:08:10 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 02:58:58 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_token_matrix(char **res, int num_col)
{
	while (num_col)
	{
		free(res[num_col - 1]);
		num_col--;
	}
	free(res);
}

void	skip_delimiter(int *i, const char *s, char del, t_general *data)
{
	while (s[*i] == del)
		(*i)++;
	account_quotes(s[*i], data);
}

void	find_end_of_the_word(int *i, const char *s, char del, t_general *data)
{
	while (s[*i] != del && s[*i] != '\0')
	{
		(*i)++;
		account_quotes(s[*i], data);
		if (data->qdata.quotes == 1)
		{
			(*i)++;
			while (s[*i] != '"')
				(*i)++;
		}
		else if (data->qdata.miniquotes == 1)
		{
			(*i)++;
			while (s[*i] != '\'')
				(*i)++;
		}
		account_quotes(s[*i], data);
	}
}

void	find_end_of_the_quotes_word(int *i, const char *s, char del,
		t_general *data)
{
	(*i)++;
	while (s[*i] != '"')
		(*i)++;
	account_quotes(s[*i], data);
	(*i)++;
	while (s[*i] != '\0' && s[*i] != del)
		(*i)++;
}

void	find_end_of_the_miniquotes_word(int *i, const char *s, char del,
		t_general *data)
{
	(*i)++;
	while (s[*i] != '\'')
		(*i)++;
	account_quotes(s[*i], data);
	(*i)++;
	while (s[*i] != '\0' && s[*i] != del)
		(*i)++;
}
