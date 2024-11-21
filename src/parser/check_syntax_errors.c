/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:35:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/21 13:06:30 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_pipe(t_general *data, t_token *token)
{
	if (!token->back)
		unexpected_token_message("`|'");
	else if (!token->next)
		unexpected_token_message("`|'");
	else if (token->next->type == PIPE)
		unexpected_token_message("`|'");
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int	check_input(t_general *data, t_token *token)
{
	if (!token->next)
		unexpected_token_message("`newline'");
	else if (token->next->type == PIPE)
		unexpected_token_message("`|'");
	else if (token->next->type == INPUT)
		unexpected_token_message("`<'");
	else if (token->next->type == HEREDOC)
		unexpected_token_message("`<<'");
	else if (token->next->type == OUTPUT)
		unexpected_token_message("`>'");
	else if (token->next->type == APPEND)
		unexpected_token_message("`>>'");
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int	check_heredoc(t_general *data, t_token *token)
{
	if (!token->next)
		unexpected_token_message("`newline'");
	else if (token->next->type == PIPE)
		unexpected_token_message("`|'");
	else if (token->next->type == INPUT)
		unexpected_token_message("`<'");
	else if (token->next->type == HEREDOC)
		unexpected_token_message("`<<'");
	else if (token->next->type == OUTPUT)
		unexpected_token_message("`>'");
	else if (token->next->type == APPEND)
		unexpected_token_message("`>>'");
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int	check_output(t_general *data, t_token *token)
{
	if (!token->next)
		unexpected_token_message("`newline'");
	else if (token->next->type == PIPE)
		unexpected_token_message("`|'");
	else if (token->next->type == INPUT)
		unexpected_token_message("`<'");
	else if (token->next->type == HEREDOC)
		unexpected_token_message("`<<'");
	else if (token->next->type == OUTPUT)
		unexpected_token_message("`>'");
	else if (token->next->type == APPEND)
		unexpected_token_message("`>>'");
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}

int	check_append(t_general *data, t_token *token)
{
	if (!token->next)
		unexpected_token_message("`newline'");
	else if (token->next->type == PIPE)
		unexpected_token_message("`|'");
	else if (token->next->type == OUTPUT)
		unexpected_token_message("`>'");
	else if (token->next->type == APPEND)
		unexpected_token_message("`>>'");
	else if (token->next->type == INPUT)
		unexpected_token_message("`<'");
	else if (token->next->type == HEREDOC)
		unexpected_token_message("`<<'");
	else
		return (1);
	data->exit_status = 2;
	free_tokens_list(data);
	return (0);
}
