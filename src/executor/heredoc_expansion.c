/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/10/24 19:32:31 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int check_expanded_heredoc_line_exists (char *tmp, t_env *env)
{
	t_env *env_tmp;

	env_tmp = env;

	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
			return (1);
		env_tmp = env_tmp->next;
	}

	return (0);
}


int change_expanded_heredoc_line(char **xline, char *tmp, t_env *env)
{
	t_env *env_tmp;
	int i;

	i = 0;;
	env_tmp = env;
	if (!tmp)
		return (0);
	while (env_tmp)
	{
		if ((ft_strncmp(tmp, env_tmp->name, ft_strlen(env_tmp->name) + 1) == 0))
		{
			while (env_tmp->value[i])
			{
				*xline = strjoinchar (*xline, env_tmp->value[i]);
				if (!*xline)
				{
					//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
					return (0);
				}
				i++;
			}
		}
		env_tmp = env_tmp->next;
	}
	return(1);
}


char *expand_line (char *line, t_env *env, int exit_status)
{
	char *xline;
	char *tmp;
	int i;
	char *exit_number;

	i = 0;
	xline = NULL;
	tmp = NULL;
	printf("#Expand heredoc line:\n");
	while (line[i])
	{
		if(line[i] == '$')
		{
			i++;
			if (line[i] && (ft_isalpha(line[i]) == 1 || line[i] == '_'))
			{
				while (line[i] && (ft_isalpha(line[i]) == 1 || ft_isdigit(line[i]) == 1 || line[i] == '_'))
				{
					tmp = strjoinchar (tmp, line[i]);
					if (!tmp)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
					i++;
				}
				printf ("  Contenido de la line después del $: |%s|\n", tmp);
				if (check_expanded_heredoc_line_exists (tmp, env) == 0)
				{
					xline = adapted_strjoin(xline, "");
					if (!xline)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				}
				else
				{
					if (change_expanded_heredoc_line(&xline,tmp, env) == 0)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
				}	
			}
			if (line[i] && line[i] == '?')
			{
				exit_number = ft_itoa (exit_status);
				xline = adapted_strjoin(xline, exit_number);
				if (!xline)
				{
					//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
					return (0);
				}
				i++;
			}
			else if (line[i] && ft_isdigit(line[i]) == 1)
			{
				if (line[i] == '0')
				{
					xline = adapted_strjoin(xline, "✌️ bash");
					if (!xline)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
					i++;
				}
				else 
				{
					xline = adapted_strjoin(xline, "");
					if (!xline)
					{
						//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
						return (0);
					}
					i++;
				}
				
			}			
			printf("   Contenido de xline: %s\n", xline);
			free(tmp);
			tmp = NULL;
			continue ;
		}	

		xline = strjoinchar (xline, line[i]);
		if (!xline)
		{
			//MIRAR LO QUE HAYA QUE LIBERAR Y MENSAJES DE ERROR
			return (0);
		}
		i++;
	}
	printf("**************Contenido de xline final: %s\n", xline);
	return (xline);
}
