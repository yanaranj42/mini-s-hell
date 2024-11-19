/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/19 15:46:11 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	do_unset(t_general *data, char *var)
{
	t_env	*head;

	head = data->env_lst;
	while (head)
	{
		if (ft_strncmp(head->name, var, ft_strlen(var)) == 0
			&& (ft_strlen(head->name) == ft_strlen(var)))
		{
			free(head->value);
			head->value = ft_strdup("");
			head->val = 0;
			head->hidden = 1;
			//return ;
			break ; 
		}
		head = head->next;
	}
	printf("do_unset\tname:%s - value:%s - hid[%d] - val[%d]\n", head->name, head->value, head->hidden, head->val);//BORRAR
}

int	ft_unset(t_general *data, t_cmd *cmd)
{
	//t_env	*head; //EL COMPILADOR DICE QUE ESTA VARIABLE NO SE USA, LA COMENTO PARA PODER COMPILAR. REVISAR
	char	**argv;
	int		i;

	i = 1;
	argv = cmd->argv;
	//head = data->env_lst;
	if (!argv[i])
		;
	while (argv[i])
	{
		do_unset(data, argv[i]);
		i++;
	}
	return (1);
}
