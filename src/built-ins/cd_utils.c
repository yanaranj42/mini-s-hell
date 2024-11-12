/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:03:39 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/12 16:37:17 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	upd_oldpwd(t_general *data)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	env_update(data, "OLDPWD", cwd);
}

int	env_update(t_general *data, char *k_word, char *n_value)
{
	t_env	*tmp;
	size_t	len;

	tmp = data->env_lst;
	len = ft_strlen(k_word);
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->name, k_word, len) == 0)
			&& (len = ft_strlen(tmp->name)))
		{
			tmp->value = ft_strdup(n_value);
			if (!tmp->value)
				return (0);
			tmp->hidden = 0;
			la var vuelva a estar visible return (1);
		}
		tmp = tmp->next;
	}
	printf("VAR: %s [%s]\n", k_word, data->env_lst->value); // BORRAR???
	return (0);
}

int	check_dir(char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == 0)
	{
		if (S_ISDIR(stats.st_mode))
			return (1);
	}
	return (0);
}

int	error_dir(t_general *data, char *path)
{
	ft_putstr_fd("minishell: cd: ", STDOUT);
	if (path)
		ft_putstr_fd(path, STDOUT);
	else
	{
		ft_putstr_fd("error retrieving current directory: ", STDERR);
		ft_putstr_fd("getcwd: cannot access parent directories", STDERR);
	}
	ft_putstr_fd(": No such file or directory\n", STDOUT);
	data->exit_status = 1;
	return (0);
}
