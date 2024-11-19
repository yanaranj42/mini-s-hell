/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/19 02:04:51 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_expanded_heredoc_line_exists(char *tmp, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
			return (1);
		env_tmp = env_tmp->next;
	}
	return (0);
}

int	change_expanded_heredoc_line(char **xline, char *tmp, t_env *env)
{
	t_env	*env_tmp;
	int		i;

	i = 0;
	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			while (env_tmp->value[i])
			{
				*xline = strjoinchar(*xline, env_tmp->value[i]);
				if (!*xline)
					return (0);
				i++;
			}
		}
		env_tmp = env_tmp->next;
	}
	return (1);
}

int	there_is_heredoc_expansion_to_manage(char *line, int *i, char **xline,
		t_general *data)
{
	if (line[*i] && (ft_isalpha(line[*i]) == 1 || line[*i] == '_'))
	{
		if (expand_heredoc_regular_variable(line, i, data->env_lst, xline) == 0)
			return (0);
	}
	else if (line[*i] && line[*i] == '?')
	{
		if (expand_heredoc_exit_status_variable(data->exit_status, xline,
				i) == 0)
			return (0);
	}
	else if (line[*i] && ft_isdigit(line[*i]) == 1)
	{
		if (expand_heredoc_digit_variable(line, xline, i) == 0)
			return (0);
	}
	return (1);
}

char	*expand_line(char *line, t_general *data)
{
	char	*xline;
	int		i;

	i = 0;
	xline = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (there_is_heredoc_expansion_to_manage(line, &i, &xline,
					data) == 0)
				return (0);
			continue ;
		}
		xline = strjoinchar(xline, line[i]);
		if (!xline)
			return (0);
		i++;
	}
	return (xline);
}
