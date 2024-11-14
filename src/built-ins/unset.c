/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/12 16:43:57 by mfontser         ###   ########.fr       */
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
			&& head->hidden == 0)
		{
			head->hidden = 1;
			return ;
		}
		head = head->next;
	}
}

int	ft_unset(t_general *data, t_cmd *cmd)
{
	//t_env	*head; //EL COMPILADOR DICE QUE ESTA VARIABLE NO SE USA, LA COMENTO PARA PODER COMPILAR. REVISAR
	char	**argv;
	int		i;

	i = 1;
	argv = cmd->argv;
	//head = data->env_lst;
	// if (!argv[i])
	// 	;  //AQUI FALTA O SOBRA ALGO. LO COMENTO PARA QUE ME DEJE COMPILAR
	while (argv[i])
	{
		do_unset(data, argv[i]);
		i++;
	}
	return (1);
}
