/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   regular_conversion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/18 12:43:57 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	expansor_variable_has_space(char *tmp, t_env *env)
{
	t_env	*env_tmp;

	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			if (ft_strchr(env_tmp->value, ' '))
				return (1);
		}
		env_tmp = env_tmp->next;
	}
	return (0);
}

int	manage_regular_variable(t_xtkn *xtkn, t_token *token, char *tmp, t_env *env)
{
	if (expansor_variable_has_space(tmp, env) && xtkn->type == FILE_REDIRECTION)
	{
		xtkn->content = ft_strdup(token->content);
		if (!xtkn->content)
		{
			free(tmp);
			return (0);
		}
	}
	else if (change_expansor_variable(xtkn, tmp, env) == 0)
	{
		free(tmp);
		return (0);
	}
	return (1);
}

int	manage_inexistent_regular_variable(t_xtkn *xtkn, t_token *token, char *tmp,
		int *i)
{
	if (!xtkn->content && !token->content[*i] && token->back
		&& (token->back->type == INPUT || token->back->type == OUTPUT
			|| token->back->type == APPEND))
	{
		xtkn->content = ft_strdup(token->content);
		if (!xtkn->content)
		{
			free(tmp);
			return (0);
		}
	}
	return (1);
}

int	regular_conversion(t_convert *info, t_token *token, t_xtkn *xtkn,
		t_env *env)
{
	if (xtkn->back && xtkn->back->type == HEREDOC)
	{
		if (build_heredoc_delimiter(xtkn, info->tmp) == 0)
			return (0);
	}
	else
	{
		if (check_expansor_variable_exists(info->tmp, env) == 0)
		{
			if (manage_inexistent_regular_variable(xtkn, token, info->tmp,
					info->i) == 0)
				return (0);
		}
		else
		{
			if (manage_regular_variable(xtkn, token, info->tmp, env) == 0)
				return (0);
		}
	}
	return (1);
}
