/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:03:04 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 16:23:48 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	check_executor_type(t_general *data)
{
	t_cmd	*cmd;

	cmd = data->first_cmd;
	data->builtin = is_builtin(cmd);
	if (cmd->argv[0] && data->builtin != 0 && !cmd->next)
		return (1);
	return (0);
}

int	do_execution(t_general *data, int *builtin_only)
{
	if (check_executor_type(data) == 1)
	{
		*builtin_only = 1;
		if (builtin_execution_only(data) == 0)
			return (0);
	}
	else if (get_children(data, count_commands(data), 0) == 0)
		return (0);
	return (1);
}
