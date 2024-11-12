/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:23:07 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/12 16:36:10 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*get_env_path(t_general *data, char *k_word)
{
	t_env	*tmp;
	int		len;

	if (!data || !k_word)
		return (0);
	tmp = data->env_lst;
	if (ft_strlen(k_word) > ft_strlen(tmp->name))
		len = ft_strlen(k_word);
	else
		len = ft_strlen(tmp->name);
	while (tmp)
	{
		if (ft_strncmp(k_word, tmp->name, len) == 0 && tmp->hidden == 0)
			return (tmp->value);
		else
			tmp = tmp->next;
	}
	return (NULL);
}

int	go_to_path(int opt, t_general *data)
{
	int		ret;
	char	*env_path;

	env_path = NULL;
	if (opt == 0)
	{
		upd_oldpwd(data);
		env_path = get_env_path(data, "HOME");
		if (!env_path)
			return (ft_putendl_fd("minishell: cd: HOME is not set", 2), 0);
	}
	if (opt == 1)
	{
		env_path = get_env_path(data, "OLDPWD");
		if (!env_path)
			return (ft_putendl_fd("minish: cd: OLDPWD not set", STDOUT), -1);
		upd_oldpwd(data);
	}
	ret = chdir(env_path);
	env_update(data, "PWD", env_path);
	ft_pwd(data->env_lst);
	return (ret);
}

int	do_oldpwd(t_general *data, char **arg)
{
	int	cd_ret;

	cd_ret = 0;
	if (arg[1][1] != '\0')
		return (error_cd_last(data, arg[1][1], 1));
	cd_ret = go_to_path(1, data);
	return (cd_ret);
}

int	ft_cd(t_general *data, char **arg)
{
	int		cd_ret;
	char	dir[PATH_MAX];

	cd_ret = 0;
	if (!arg[1] || arg[1][0] == '~')
		return (go_to_path(0, data));
	else if (arg[1][0] == '-' && !arg[2])
		cd_ret = do_oldpwd(data, arg);
	else if (arg[2] != NULL)
		return (error_cd_last(data, '\0', 0));
	else
	{
		if (!check_dir(arg[1]))
			return (error_dir(data, arg[1]));
		upd_oldpwd(data);
		cd_ret = chdir(arg[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		else if (cd_ret != 0)
			printf(RED "ERROR de args" END);
		getcwd(dir, PATH_MAX);
		if (!check_dir(dir))
			return (error_dir(data, NULL));
		env_update(data, "PWD", dir);
		ft_pwd(data->env_lst);
	}
	return (cd_ret);
}
