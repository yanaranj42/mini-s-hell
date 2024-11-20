/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/20 16:41:07 by yanaranj         ###   ########.fr       */
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
			break ; 
		}
		head = head->next;
	}
	//printf("do_unset\tname: %s - value: %s - hid[%i] - val[%i]\n", head->name, head->value, head->hidden, head->val);
}

int	ft_unset(t_general *data, t_cmd *cmd)
{
	char	**argv;
	int		i;

	i = 1;
	argv = cmd->argv;
	if (!argv[i] || argv[i][0] == '_')
		return (1);
	while (argv[i])
	{
		do_unset(data, argv[i]);
		i++;
	}
	return (1);
}
