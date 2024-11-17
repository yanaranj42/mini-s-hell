/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_specific_variables.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/09 20:14:28 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	expand_heredoc_exit_status_variable(int exit_status, char **xline, int *i)
{
	char	*exit_number;

	exit_number = ft_itoa(exit_status);
	*xline = adapted_strjoin(*xline, exit_number);
	if (!*xline)
		return (0);
	i++;
	return (1);
}

int	expand_heredoc_digit_variable(char *line, char **xline, int *i)
{
	if (line[*i] == '0')
	{
		*xline = adapted_strjoin(*xline, "✌️ bash");
		if (!*xline)
			return (0);
		(*i)++;
	}
	else
	{
		*xline = adapted_strjoin(*xline, "");
		if (!*xline)
			return (0);
		(*i)++;
	}
	return (1);
}

char	*identify_heredoc_variable_to_expand(char *line, int *i)
{
	char	*tmp;

	tmp = NULL;
	while (line[*i] && (ft_isalpha(line[*i]) == 1 || ft_isdigit(line[*i]) == 1
			|| line[*i] == '_'))
	{
		tmp = strjoinchar(tmp, line[*i]);
		if (!tmp)
			return (NULL);
		(*i)++;
	}
	return (tmp);
}

int	expand_heredoc_regular_variable(char *line, int *i, t_env *env,
		char **xline)
{
	char	*tmp;

	tmp = identify_heredoc_variable_to_expand(line, i);
	if (check_expanded_heredoc_line_exists(tmp, env) == 0)
	{
		*xline = adapted_strjoin(*xline, "");
		if (!*xline)
			return (0);
	}
	else
	{
		if (change_expanded_heredoc_line(xline, tmp, env) == 0)
			return (0);
	}
	free(tmp);
	return (1);
}
