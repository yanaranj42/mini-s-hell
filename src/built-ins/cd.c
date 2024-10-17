/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 12:23:07 by yanaranj          #+#    #+#             */
/*   Updated: 2024/10/17 05:25:01 by yanaranj         ###   ########.fr       */
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
		return (0);
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

int	env_update(t_general *data, char *k_word, char *n_value)
{
	t_env	*tmp;
	size_t	len;

	tmp = data->env_lst;
	len = ft_strlen(k_word);
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->name, k_word, len) == 0) \
				&& (len = ft_strlen(tmp->name)))
		{
			tmp->value = ft_strdup(n_value);
			if (!tmp->value)
				return (0);
			return (1);
		}
		if (!tmp->name)
			add_upd_env(data, k_word, n_value);
		tmp = tmp->next;
	}
	return (0);
}
//vamos a hacer que nos actualice el OLDPWD, ya que el PWD lo podemos hacer desde
//update_env();
int	update_pwd(t_general *data)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (0);
	printf("OLD: %s\n", cwd);
	if (env_update(data, "OLDPWD", cwd))
		return (1);
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
			return (0);
		}
	}
	//entra en este  error cuando "unset OLDPWD". Tenemos que crear nuevamente la var si corresponde
	else if (opt == 1)
	{
		env_path = get_env_path(data, "OLDPWD");
		if (!env_path)
		{	
			return (ft_putendl_fd("minish: cd: OLDPWD not seted", STDOUT), 0);
			//add_upd_env(data, "OLDPWD", "HOLA");
			//return (0);
		}
		update_pwd(data);
	}
	ret = chdir(env_path);
	//update_pwd(data);
	env_update(data, "PWD", env_path);
	return (ret);
}

/*este argv sera el cmd que recibamos*/

//NO ME ACTUALIZA EL OLDPWD AL LLAMAR AL ENV
int	ft_cd(t_general *data)
{
	int		cd_ret;
	char	**arg;
	char	dir[PATH_MAX];

	arg = data->first_cmd->argv;
	if (!arg[1] || arg[1][0] == '~')//HOME
		return (go_to_path(0, data));
	if (arg[1][0] == '-' && !arg[2]) //LAST CHECKED DIR + ERRORS (quiza void??)
	{
		if (arg[1][1] != '\0')
			return (error_cd_last(data, arg[1][1], 1));
		cd_ret = go_to_path(1, data);
	}
	else if (arg[2] != NULL)
		return (error_cd_last(data, '\0', 0));
	else
	{
		update_pwd(data);
		cd_ret = chdir(arg[1]);
		if (cd_ret < 0)
			cd_ret *= -1;
		else if (cd_ret != 0)
			printf(RED"ERROR de args"END);
		getcwd(dir, PATH_MAX);
		env_update(data, "PWD", dir);
	}
	return (cd_ret);
}
