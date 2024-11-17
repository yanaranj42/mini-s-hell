/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_pretoken.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:05:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/07 11:19:14 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	is_real_separator(char c, t_general *data)
{
	account_quotes(c, data);
	if ((c == '<' || c == '>' || c == '|') && data->qdata.quotes == 0
		&& data->qdata.miniquotes == 0)
		return (1);
	return (0);
}

int	fill_word_pretoken(t_general *data, int *i)
{
	while (data->line[*i] && is_real_separator(data->line[*i], data) == 0)
	{
		data->pretoken = strjoinchar(data->pretoken, data->line[*i]);
		if (!data->pretoken)
			return (0);
		(*i)++;
	}
	return (1);
}

int	fill_separator_pretoken(t_general *data, int *i)
{
	data->pretoken = strjoinchar(data->pretoken, data->line[*i]);
	if (!data->pretoken)
		return (0);
	if (data->line[*i] == '<' && data->line[*i + 1] == '<')
	{
		(*i)++;
		data->pretoken = strjoinchar(data->pretoken, data->line[*i]);
	}
	else if (data->line[*i] == '>' && data->line[*i + 1] == '>')
	{
		(*i)++;
		data->pretoken = strjoinchar(data->pretoken, data->line[*i]);
	}
	if (!data->pretoken)
		return (0);
	(*i)++;
	return (1);
}

int	take_pretoken(t_general *data, int *i)
{
	if (data->line[*i] == ' ')
		(*i)++;
	if (data->line[*i] == '<' || data->line[*i] == '>' || data->line[*i] == '|')
	{
		if (fill_separator_pretoken(data, i) == 0)
			return (0);
	}
	else
	{
		if (fill_word_pretoken(data, i) == 0)
			return (0);
	}
	return (1);
}

int	prepare_pretoken(t_general *data, int *i, char ***argv)
{
	if (take_pretoken(data, i) == 0)
	{
		printf("Error: There have been problems preparing tokens\n");
		data->exit_status = 1;
		return (0);
	}
	*argv = ft_token_split(data->pretoken, ' ', data);
	if (!*argv)
	{
		printf("Error: There have been problems doing the token split\n");
		data->exit_status = 1;
		free(data->pretoken);
		data->pretoken = NULL;
		free_tokens_list(data);
		return (0);
	}
	return (1);
}
