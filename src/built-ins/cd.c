/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:23:07 by yanaranj          #+#    #+#             */
/*   Updated: 2024/08/13 16:15:18 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_path(t_general *data, char *k_word)
{
}

int	env_update(t_env *head, char *k_word, char *n_value)
{
}

int	update_pwd(t_general *data)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (!getcwd(cwd, PATH_MAX));
		return (FAIL);
	if (env_update(data->env_lst, "OLDPWD", cwd))
		return (SUCCESS);
	return (0); //que hace si no ha entrado a ninguna de las condiciones??
}

int	go_to_path(int opt, t_general *data)
{
	int		ret;	
	char	*env_path;

	env_path = NULL;
	if (opt == 0)
	{
		update_pwd(data);
		env_path = get_env_path(data, "HOME");
		if (!env_path)
		{
			ft_putendl_fd("minishell: cd: HOME is not set", STDERR);
			return (FAIL);
		}
	}
	else if (opt == 1)
	{
		env_path = get_env_path(data, "OLDPWD");
		if (!env_path)
			return (ft_putendl_fd("minish: cd: OLDPWD not seted", STDERR), FAIL);
		update_pwd(data);
	}
	ret = chdir(env_path);
	return (ret);	
}

/*este argv sera el cmd que recibamos*/
int ft_cd(t_general *data)
{
	//t_env	*env;
    int		i;
    int		cd_ret;

    i = 0;
	//if (!argv[1])
	if (!data->first_token->argv[1])
		go_to_path(0, data);
    return (0);
}
