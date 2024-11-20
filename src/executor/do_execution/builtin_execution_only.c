/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_execution_only.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 00:59:03 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_father_redirs_2(t_general *data, t_cmd *first_cmd)
{
	t_redir	*redir;

	redir = first_cmd->first_redir;
	if (redir->type == INPUT)
	{
		if (check_father_input_redir(first_cmd, redir, data) == 0)
			return (0);
	}
	else if (redir->type == HEREDOC)
	{
		if (check_father_heredoc_redir(first_cmd, redir, data) == 0)
			return (0);
	}
	return (1);
}

int	check_father_redirs_1(t_general *data, t_cmd *first_cmd)
{
	t_redir	*redir;

	redir = first_cmd->first_redir;
	while (redir)
	{
		if (redir->type == OUTPUT)
		{
			if (check_father_output_redir(first_cmd, redir, data) == 0)
				return (0);
		}
		else if (redir->type == APPEND)
		{
			if (check_father_append_redir(first_cmd, redir, data) == 0)
				return (0);
		}
		else
			check_father_redirs_2(data, first_cmd);
		redir = redir->next;
	}
	return (1);
}

int	builtin_execution_only(t_general *data)
{
	int	copy_stdin;
	int	copy_stdout;

	copy_stdin = dup(STDIN_FILENO);
	copy_stdout = dup(STDOUT_FILENO);
	if (check_father_redirs_1(data, data->first_cmd) == 0)
		return (0);
	execute_builtin(data, data->first_cmd);
	if (dup2(copy_stdin, 0) == -1)
	{
		free_builtin_execution_only(data, &copy_stdin, &copy_stdout,
			"Problem with dup2 of builtin std_input");
		exit(1);
	}
	if (dup2(copy_stdout, 1) == -1)
	{
		free_builtin_execution_only(data, &copy_stdin, &copy_stdout,
			"Problem with dup2 of builtin std_output");
		exit(1);
	}
	close(copy_stdin);
	close(copy_stdout);
	return (1);
}
