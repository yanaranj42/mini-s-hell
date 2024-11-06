/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:39:24 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 04:59:32 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	delete_spaces(t_general *data)
{
	char	*tmp;

	tmp = data->line;
	data->line = ft_strtrim(data->line, " ");
	free(tmp);
}

int	review_closed_quotes(t_general *data)
{
	int	i;

	i = 0;
	init_quote_values(data);
	while (data->line[i])
	{
		if (data->line[i] == '"' && data->qdata.miniquotes == 0)
		{
			if (data->qdata.quotes == 0)
				data->qdata.quotes = 1;
			else if (data->qdata.quotes == 1)
				data->qdata.quotes = 0;
		}
		if (data->line[i] == '\'' && data->qdata.quotes == 0)
		{
			if (data->qdata.miniquotes == 0)
				data->qdata.miniquotes = 1;
			else if (data->qdata.miniquotes == 1)
				data->qdata.miniquotes = 0;
		}
		i++;
	}
	if (data->qdata.quotes == 1 || data->qdata.miniquotes == 1)
		return (0);
	return (1);
}

int	fill_updated_line(t_general *data)
{
	free(data->line);
	data->line = ft_strdup(data->pretoken);
	if (!data->line)
	{
		free(data->pretoken);
		data->pretoken = NULL;
		return (0);
	}
	free(data->pretoken);
	data->pretoken = NULL;
	return (1);
}

int	delete_useless_spaces(t_general *data)
{
	int	i;

	i = 0;
	init_quote_values(data);
	while (data->line[i])
	{
		if ((data->line[i] == '"') || (data->line[i] == '\''))
			account_quotes(data->line[i], data);
		else if (data->line[i] == ' ' && data->line[i + 1] == ' '
			&& data->qdata.quotes == 0 && data->qdata.miniquotes == 0)
		{
			i++;
			continue ;
		}
		data->pretoken = strjoinchar(data->pretoken, data->line[i]);
		if (!data->pretoken)
			return (0);
		i++;
	}
	if (fill_updated_line(data) == 0)
		return (0);
	return (1);
}

int	lexer(t_general *data)
{
	delete_spaces(data);
	if (data->line[0] == '\0')
	{
		data->exit_status = 127;
		return (0);
	}
	if (review_closed_quotes(data) == 0)
	{
		printf("Error: The quotes are not closed properly\n");
		data->exit_status = 1;
		return (0);
	}
	if (delete_useless_spaces(data) == 0)
	{
		printf("Error: There have been problems cleaning useless spaces\n");
		data->exit_status = 1;
		return (0);
	}
	return (1);
}
