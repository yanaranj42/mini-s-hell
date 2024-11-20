/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:24:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 01:25:54 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	build_command_path(char **tmp, char **tmp2, char *str, char *cmd_argv)
{
	*tmp = ft_strjoin(str, "/");
	if (!*tmp)
		return (0);
	*tmp2 = ft_strjoin(*tmp, cmd_argv);
	if (!*tmp2)
	{
		free(*tmp);
		return (0);
	}
	return (1);
}

char	*check_cmd_current_directory(char *cmd_argv)
{
	char	cwd[PATH_MAX];
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if (getcwd(cwd, PATH_MAX))
	{
		if (build_command_path(&tmp, &tmp2, cwd, cmd_argv) == 0)
			return (NULL);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
			{
				free(tmp);
				return (tmp2);
			}
			else
				permission_denied(cmd_argv);
		}
	}
	free(tmp);
	free(tmp2);
	return (NULL);
}

char	*check_cmd_relative_path(char *cmd_argv, char *path)
{
	char	*tmp;
	char	*tmp2;

	if (build_command_path(&tmp, &tmp2, path, cmd_argv) == 0)
		return (NULL);
	if (access(tmp2, F_OK) == 0)
	{
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			return (tmp2);
		}
		else
			permission_denied(cmd_argv);
	}
	free(tmp);
	free(tmp2);
	return (NULL);
}

char	*check_cmd_absolut_path(char *cmd_argv)
{
	if (ft_strchr(cmd_argv, '/'))
	{
		if (access(cmd_argv, F_OK) == -1)
			no_such_file_or_directory(cmd_argv);
		else if (access(cmd_argv, X_OK) == 0)
		{
			cmd_argv = ft_strdup(cmd_argv);
			if (!cmd_argv)
				return (NULL);
			return (cmd_argv);
		}
		else
			permission_denied(cmd_argv);
	}
	return (NULL);
}

void	check_cmd_path(t_cmd *cmd, char **paths, t_env *env)
{
	t_env 	*tmp;
	int		flag;

	flag = 0;
	tmp = env;
	cmd->path = check_cmd_current_directory(cmd->argv[0]);
	if (!cmd->path)
	{
		while (tmp) //Este while y la flag de la condicion del siguiente if, son porque en el unset y export, en vez de eliminar la variable, la oculta, por lo que si me hacen unset no entraria nunca. A modo apaño.
		{
			if (ft_strncmp("PATH", tmp->name, 5) == 0 && tmp->val == 0)
				flag = 1;
			tmp = tmp->next;
		}
		if (!paths || flag == 1)  // hasta aqui
		{
			cmd->path = check_cmd_absolut_path(cmd->argv[0]);
			if (cmd->path == NULL)
				command_not_found(cmd->argv[0]);
		}
		else
			cmd->path = check_cmd_access(paths, cmd->argv[0]);
	}
}
