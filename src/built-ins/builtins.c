/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 01:50:35 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 16:22:25 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	execute_builtin(t_general *data, t_cmd *cmd)
{
	if (data->builtin == 1)
		ft_echo(cmd->argv);
	else if (data->builtin == 2)
		ft_cd(data, cmd->argv);
	else if (data->builtin == 3)
		ft_pwd(data->env_lst);
	else if (data->builtin == 4)
		ft_env(data->env_lst);
	else if (data->builtin == 5)
		ft_exit(data);
	else if (data->builtin == 6)
		ft_export(data);
	else if (data->builtin == 7)
		ft_unset(data, cmd);
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd || !cmd->argv[0])
		return (0);
	else if (ft_strncmp("echo", cmd->argv[0], 5) == 0)
		return (1);
	else if (ft_strncmp("cd", cmd->argv[0], 3) == 0)
		return (2);
	else if (ft_strncmp("pwd", cmd->argv[0], 4) == 0)
		return (3);
	else if (ft_strncmp("env", cmd->argv[0], 4) == 0)
		return (4);
	else if (ft_strncmp("exit", cmd->argv[0], 5) == 0)
		return (5);
	else if (ft_strncmp("export", cmd->argv[0], 7) == 0)
		return (6);
	else if (ft_strncmp("unset", cmd->argv[0], 6) == 0)
		return (7);
	return (0);
}
