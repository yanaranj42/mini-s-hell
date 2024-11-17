/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 04:18:46 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 06:40:39 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_data_paths(t_general *data)
{
	int	i;

	i = 0;
	if (data->paths == NULL)
		return ;
	while (data->paths[i])
	{
		free(data->paths[i]);
		i++;
	}
	free(data->paths);
	data->paths = NULL;
}

void	free_matrix_env(t_general *data)
{
	int	i;

	i = 0;
	if (data->env_matrix == NULL)
		return ;
	while (data->env_matrix[i])
	{
		free(data->env_matrix[i]);
		i++;
	}
	free(data->env_matrix);
	data->env_matrix = NULL;
}

void	free_xtkns_list(t_general *data)
{
	t_xtkn	*tmp_xtkn;

	while (data->first_xtkn)
	{
		tmp_xtkn = data->first_xtkn->next;
		free(data->first_xtkn->content);
		free(data->first_xtkn);
		data->first_xtkn = NULL;
		data->first_xtkn = tmp_xtkn;
	}
}

void	free_builtin_execution_only(t_general *data, int *copy_stdin,
		int *copy_stdout, char *message)
{
	perror_message(NULL, message);
	free_executor_process(data);
	close(*copy_stdin);
	close(*copy_stdout);
}

void	free_executor_process(t_general *data)
{
	free_matrix_env(data);
	free_data_paths(data);
	free_cmd(data);
	data->exit_status = 1;
}
