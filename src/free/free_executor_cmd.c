/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_executor_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:18:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 05:09:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_cmd_argv(t_general *data, int *i)
{
	while (data->first_cmd->argv && data->first_cmd->argv[*i])
	{
		free(data->first_cmd->argv[*i]);
		(*i)++;
	}
	free(data->first_cmd->argv);
	data->first_cmd->argv = NULL;
}

void	free_cmd_redir(t_general *data)
{
	t_redir	*tmp_redir;

	while (data->first_cmd->first_redir)
	{
		tmp_redir = data->first_cmd->first_redir->next;
		free(data->first_cmd->first_redir->file_name);
		free(data->first_cmd->first_redir);
		data->first_cmd->first_redir = tmp_redir;
	}
	free(data->first_cmd->first_redir);
	data->first_cmd->first_redir = NULL;
}

void	free_cmd(t_general *data)
{
	int		i;
	t_cmd	*tmp_cmd;

	while (data->first_cmd)
	{
		i = 0;
		tmp_cmd = data->first_cmd->next;
		free_cmd_argv(data, &i);
		free_cmd_redir(data);
		free(data->first_cmd);
		data->first_cmd = tmp_cmd;
	}
	data->first_cmd = NULL;
}

void	free_get_cmd_process(t_general *data)
{
	free_xtkns_list(data);
	free_matrix_env(data);
	free_data_paths(data);
	free_cmd(data);
	data->exit_status = 1;
}
