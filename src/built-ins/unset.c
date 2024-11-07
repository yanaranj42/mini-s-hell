/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/07 18:36:12 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	do_unset(t_general *data, char *var)
{
	t_env	*head;//tiene la ref al inicio de la lista y se  va modificando
	
	head = data->env_lst;//el puntero esta al inicio de la lista y es este el que estoy moviendo
	while (head) //agrego la condicion para que no entre una y otra vez si llamamos a la misma var
	{
		if (ft_strncmp(head->name, var, ft_strlen(var)) == 0 && head->hidden == 0)
		{
			head->hidden = 1;
			return ;
		}
		head = head->next;
	}
	printf("NO  HAGO NADA\n");
}
int	ft_unset(t_general *data, t_cmd *cmd)
{
	t_env	*head;
	char	**argv;
	int		i;

	i = 1;
	argv = cmd->argv;
	head = data->env_lst;
	if (!argv[i])
		;
	while (argv[i])
	{
		do_unset(data, argv[i]);
		i++;
	}
	/*if (data->env_matrix)
		data->env_matrix = arr_clean(data->env_matrix);
	get_matrix_env(data, data->env_lst);
	if (!data->env_lst)
		return ((void)error_brk(data, "Malloc Error", NULL, 12), 0); */
	return (1);
}
