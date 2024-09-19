/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:46:16 by yaja              #+#    #+#             */
/*   Updated: 2024/09/19 16:30:54 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* Una vez empecemos con las pipes, checkear si debemos incluir las salidas 
 *	de los fds. Por ahora lo tenemos en todos los builtins de forma manual
*/
void	print_env(t_general *data, t_env *tmp)
{
	ft_putstr_fd("\"", STDOUT);
	if (tmp->value != NULL && data->equal == OK)
		ft_putstr_fd(tmp->value, STDOUT);
	ft_putstr_fd("\"", STDOUT);
	ft_putstr_fd("\n", STDOUT);
}

void	print_sort(t_env *own_env)
{
	t_env	*tmp;
	char	*tmp_name;
	char	*tmp_value;
	
	tmp = own_env;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (ft_strncmp(tmp->name, tmp->next->name, ft_strlen(tmp->name)) > 0)
			{
				tmp_name = tmp->name;
				tmp_value = tmp->value;
				tmp->name = tmp->next->name;
				tmp->value = tmp->next->value;
				tmp->next->name = tmp_name;
				tmp->next->value = tmp_value;
				tmp = own_env;
			}
		}
		tmp = tmp->next;
	}
}

int	print_export_lst(t_general *data, t_env *own_env)
{
	t_env	*tmp;
	
	(void)data;
	if (!own_env)
		return (1);
	print_sort(own_env);
	tmp = own_env;
	while (tmp)
	{
		ft_putstr_fd(" declare -x ", STDOUT);
		ft_putstr_fd(tmp->name, STDOUT);
		if (tmp->value)
		{
			ft_putstr_fd("=", STDOUT);
			ft_putstr_fd("\"", STDOUT);
			ft_putstr_fd(tmp->value, STDOUT);
			ft_putstr_fd("\"", STDOUT);
		}
		ft_putstr_fd("\n", STDOUT);
		tmp = tmp->next;
	}
	tmp = own_env;
	return (1);
}
//estoy checkando que el nombre de la variable de entorno sea valido y no contenga caracteres raros
//en end checkeo el ultimo char de name
int	export_opt(char *name, char *argv)
{
	int	i;
	int	end;
	
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (KO);
	i = 1;
	end = ft_strlen(name) - 1;
	while (name[i] && name[i + 1] != '=')
	{
		if (!ft_isalnum(name[i] && name[i] != '_'))
		{
			if (name[i] == '+' && (name[i + 1] || !ft_strchr(argv, '=')))
				return (KO);
			if (name[i] == ' ' || name[i] == '%' || name[i] == '/')
				return (KO);
			if (name[end] != '+' && name[end] != '=' && !(ft_isalpha(name[end])))
				return (KO);
		}
		i++;
	}
	return (OK);
}
/* Busca si la var esta en la lista. Si no esta, la agregamos a la lista env
	Si la encuentra, y el valor es NULL, hacemos un dup de "".
	Mientras la lista exista, cuando haya match en una variable, hacemos un join
	del anterior valor, y e""
no tenemos valor en la variableAQUI VA ERROR
l nuevo. Y si este es NULL, el join funciona gracia al dup
*/
void	export_plus_var(t_general *data, char *name, char *value)
{
	t_env	*env;
	char	*old_val;
	char	*env_var;

	env_var = find_env_var(data, name);
	if (!env_var)
		return ((void)add_upd_env(data, name, value));//void porque esta funcion lo es
	else
	{
		env = data->env_lst;
		if (!value)
			value = ft_strdup("");
		while (env != NULL)
		{
			if (ft_strncmp(env->name, name, ft_strlen(name)) == 0 \
				&& (ft_strlen(env->name) == ft_strlen(name)))
			{
				old_val = env->value;
				env->value = ft_strjoin(old_val, value);
				free(old_val);
				return ;
			}
			env = env->next;
		}
	}
}
