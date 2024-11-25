/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_access.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 20:04:20 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/25 00:25:18 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*check_cmd_access(char **paths, char *cmd_argv)
{
	int		i;
	char	*tmp;

	if (cmd_argv == NULL || cmd_argv[0] == '\0')
	{
		command_not_found("''");
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
	command_not_found(cmd_argv);
	return (NULL);
}
