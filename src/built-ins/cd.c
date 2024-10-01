/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:23:07 by yanaranj          #+#    #+#             */
/*   Updated: 2024/09/23 15:54:32 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

// recibimos la palabra HOME o OLDPWD
/* con la var len hago, busco cual de las dos palabras es mas larga y asignamos
	a len el valor correcto para hacer el strncmp*/
char	*get_env_path(t_general *data, char *k_word)
{
	t_env	*tmp;
	int		len;

	if (!data || !k_word)
		return (KO);
	tmp = data->env_lst;
	if (ft_strlen(k_word) > ft_strlen(tmp->name))
		len = ft_strlen(k_word);
	else
		len = ft_strlen(tmp->name);
	while (tmp)
	{
		if (ft_strncmp(k_word, tmp->name, len) == 0)
			return (tmp->value);
		else
			tmp = tmp->next;
	}
	return (NULL);
}

int	env_update(t_env *head, char *k_word, char *n_value)
{
	t_env	*tmp;
	size_t	len;

	tmp = head;
	len = ft_strlen(k_word);
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->name, k_word, len) == 0) \
				&& (len = ft_strlen(tmp->name)))
		{
			tmp->value = ft_strdup(n_value);
			if (!tmp->value)
				return (KO);
			return (OK);
		}
		tmp = tmp->next;
	}
	return (KO);
}

int	update_pwd(t_general *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (KO);
	if (env_update(data->env_lst, "OLDPWD", cwd))
		return (OK);
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
			ft_putendl_fd("minishell: cd: HOME is not set", 2);
			return (KO);
		}
	}
	else if (opt == 1)
	{
		env_path = get_env_path(data, "OLDPWD");
		if (!env_path)
			return (ft_putendl_fd("minish: cd: OLDPWD not seted", 2), KO);
		update_pwd(data);
	}
	ret = chdir(env_path);
	return (ret);
}

/*este argv sera el cmd que recibamos*/
int	ft_cd(t_general *data)
{
	int		cd_ret;
	char	**arg;

	arg = data->first_token->argv;
	//if (!argv[1])
	if (!arg[1] || arg[1][0] == '~') //HOME
	{
		printf("%d\n", ft_pwd());
		return (go_to_path(0, data));
	}
	if (ft_strncmp(arg[1], "-", 1) == 0) //LAST CHECKED DIR
	{
		cd_ret = go_to_path(1, data);
		printf("%d\n", ft_pwd());
	}
	else
	{
		update_pwd(data);
		cd_ret = chdir(arg[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		else if (cd_ret != 0)
			printf(RED"ERROR de args"END);
		printf("%d\n", ft_pwd()); //CHANGE SPECIFIC DIR
	}
	return (cd_ret);
}
