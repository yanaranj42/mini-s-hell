/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 11:46:16 by yaja              #+#    #+#             */
/*   Updated: 2024/11/20 16:53:31 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static void	swap_node(t_env *a, t_env *b)
{
	char	*name;
	char	*value;
	int		hid;
	int		val;

	name = a->name;
	value = a->value;
	hid = a->hidden;
	val = a->val;
	a->name = b->name;
	a->value = b->value;
	a->hidden = b->hidden;
	a->val = b->val;
	b->name = name;
	b->value = value;
	b->hidden = hid;
	b->val = val;
}

void	print_sort(t_env *own_env)
{
	t_env	*tmp;

	tmp = own_env;
	while (tmp)
	{
		if (tmp->next && tmp->hidden == 0)
		{
			if (ft_strncmp(tmp->name, tmp->next->name, \
			ft_strlen(tmp->name)) > 0)
			{
				swap_node(tmp, tmp->next);
				tmp = own_env;
			}
		}
		tmp = tmp->next;
	}
}

int	print_export_lst(t_env *own_env, int equal)
{
	t_env	*tmp;

	(void)equal;//BORRAR
	if (!own_env)
		return (1);
	print_sort(own_env);
	tmp = own_env;
	while (tmp)
	{
		if (tmp->hidden == 0 && ft_strncmp(tmp->name, "_", 1) != 0)
		{
			ft_putstr_fd(" declare -x ", STDOUT);
			ft_putstr_fd(tmp->name, STDOUT);
			if (tmp->val == 1)//me printa las vars aunque no tengan valor
			{
				ft_putstr_fd("=", STDOUT);
				ft_putstr_fd("\"", STDOUT);
				ft_putstr_fd(tmp->value, STDOUT);
				ft_putstr_fd("\"", STDOUT);
			}
			ft_putstr_fd("\n", STDOUT);
		}
		tmp = tmp->next;
	}
	tmp = own_env;
	return (1);
}

int	export_opt(char *name, char *argv)
{
	int	i;
	int	end;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	i = 1;
	end = ft_strlen(name) - 1;
	while (name[i] && name[i + 1] != '=')
	{
		if (!ft_isalnum(name[i] && name[i] != '_'))
		{
			if (name[i] == '+' && (name[i + 1] || !ft_strchr(argv, '=')))
				return (0);
			if (name[i] == ' ' || name[i] == '%' || name[i] == '/')
				return (0);
			if (name[end] != '+' && name[end] != '='
				&& !(ft_isalnum(name[end])))
				return (0);
		}
		i++;
	}
	return (1);
}

void	export_plus_var(t_general *data, char *name, char *value)
{
	t_env	*env;
	char	*old_val;
	char	*env_var;

	env_var = find_env_var(data, name);
	if (!env_var || ft_strncmp(name, "_", 1) == 0)
		return ((void)add_upd_env(data, name, value));
	else
	{
		env = data->env_lst;
		if (!value)
			value = ft_strdup("");
		while (env)
		{
			if (ft_strncmp(env->name, name, ft_strlen(name)) == 0
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
