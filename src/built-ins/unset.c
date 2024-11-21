/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:20:52 by yanaranj          #+#    #+#             */
/*   Updated: 2024/11/21 19:32:55 by mfontser         ###   ########.fr       */
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
}

int	ft_unset(t_general *data, t_cmd *cmd)
{
	char	**argv;
	int		i;

	i = 1;
	argv = cmd->argv;
	if (!argv[i] || argv[i][0] == '_')
		return (1);
	if (argv[i][0] == '-')
		return (error_opt("unset", argv[i][1]));
	while (argv[i])
	{
		do_unset(data, argv[i]);
		i++;
	}
	return (0);
}
