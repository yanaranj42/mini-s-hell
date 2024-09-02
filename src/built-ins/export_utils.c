/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaja <yaja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:46:16 by yaja              #+#    #+#             */
/*   Updated: 2024/09/02 14:55:39 by yaja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/* Una vez empecemos con las pipes, checkear si debemos incluir las salidas 
 *	de los fds. Por ahora lo tenemos en todos los builtins de forma manual
*/
void	print_env(t_env *tmp)
{
	ft_putstr_fd("=", STDOUT);
	ft_putstr_fd("\"", STDOUT);
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
			if (strcmp(tmp->name, tmp->next->name) > 0)
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
int	print_export_lst(t_env *own_env)
{
	t_env	*tmp;

	if (!own_env)
		return (1);
	print_sort(own_env);
	tmp = own_env;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", STDOUT);
		ft_putstr_fd(tmp->name, STDOUT);
		if (tmp->value)
			print_env(tmp);
		else
			ft_putstr_fd("\n", STDOUT);
		tmp = tmp->next;
	}
	tmp = own_env;
	return (1);
}
//estoy checkando que el nombre de la variable de entorno sea valido y no contenga caracteres raros
int	export_opt(char *name)
{
	int	i;

	if (!name || (ft_isalpha(name[0]) && name[0] != '_'))
		return (KO);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i] && name[i] != '_'))
		{
			if (name[i] == '+' && name[i + 1])
				return (KO);
			if (name[i] == ' ' || name[i] == '%' || name[i] == '/')
				return (KO);
			if (name[i] != '+' && name[i] != '=')
				return (KO);
		}
		i++;
	}
	return (OK);
}