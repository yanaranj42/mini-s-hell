/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 15:24:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/04 19:24:59 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "libft.h"

int build_command_path (char	**tmp, char	**tmp2, char *str, char *cmd_argv)
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


char *check_cmd_current_directory(char *cmd_argv)
{
	char cwd[PATH_MAX];
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	if(getcwd(cwd, PATH_MAX))
	{
		if (build_command_path (&tmp, &tmp2, cwd, cmd_argv) == 0)
			return (NULL);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
			{
				free(tmp);
				return (tmp2);
			}
			else
				permission_denied (cmd_argv);
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

	if (build_command_path (&tmp, &tmp2, path, cmd_argv) == 0)
			return (NULL);
	if (access(tmp2, F_OK) == 0)
	{
		if (access(tmp2, X_OK) == 0)
		{
			free(tmp);
			return (tmp2);
		}
		else
			permission_denied (cmd_argv);
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
			no_such_file_or_directory (cmd_argv);
		else if (access(cmd_argv, X_OK) == 0)
		{
			cmd_argv = ft_strdup(cmd_argv);
			if (!cmd_argv)
				return (NULL);
			return (cmd_argv);
		}
		else
			permission_denied (cmd_argv);
	}
	return (NULL);
}

char	*check_cmd_access(char **paths, char *cmd_argv)
{
	int		i;
	char	*tmp;

	if (cmd_argv == NULL)
	{
		command_not_found ("''"); 
		return (NULL);
	}
	tmp = check_cmd_absolut_path(cmd_argv);
	if (tmp != NULL)
		return (tmp);
	i = 0;
	while (paths && paths[i])
	{
		tmp = check_cmd_relative_path(cmd_argv, paths[i]);
		{
			if (tmp != NULL)
				return (tmp);
		}
		i++;
	}
	command_not_found (cmd_argv);
	return (NULL);
}


void	check_cmd_path(t_cmd *cmd, char **paths)
{
	cmd->path = check_cmd_current_directory(cmd->argv[0]);
	if (!cmd->path)
	{
		if (!paths) 
		{
			cmd->path = check_cmd_absolut_path(cmd->argv[0]);
			if (cmd->path == NULL)
				command_not_found (cmd->argv[0]);
		}
		else
			cmd->path = check_cmd_access(paths, cmd->argv[0]);
	}
}
