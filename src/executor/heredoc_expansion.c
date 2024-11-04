/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 21:34:31 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/04 20:14:02 by mfontser         ###   ########.fr       */
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
					return (0);
				i++;
			}
		}
		env_tmp = env_tmp->next;
	}
	return(1);
}




char *identify_heredoc_variable_to_expand (char *line, int *i)
{
	char *tmp;

	tmp = NULL;
	while (line[*i] && (ft_isalpha(line[*i]) == 1 || ft_isdigit(line[*i]) == 1 || line[*i] == '_'))
	{
		tmp = strjoinchar (tmp, line[*i]);
		if (!tmp)
			return (NULL);
		(*i)++;
	}
	return (tmp);
}


int expand_heredoc_regular_variable (char *line,  int *i, t_env *env, char **xline)
{
	char *tmp;

	tmp = identify_heredoc_variable_to_expand (line, i);
	printf ("  Contenido de la line después del $: |%s|\n", tmp);
	if (check_expanded_heredoc_line_exists (tmp, env) == 0)
	{
		*xline = adapted_strjoin(*xline, "");
		if (!*xline)
			return (0);
	}
	else
	{
		if (change_expanded_heredoc_line(xline, tmp, env) == 0)
			return (0);
	}
	free(tmp);
	return (1);	
}


int expand_heredoc_exit_status_variable(int exit_status, char **xline, int *i)
{
	char *exit_number;

	exit_number = ft_itoa (exit_status);
	*xline = adapted_strjoin(*xline, exit_number);
	if (!*xline)
		return (0);
	i++;
	return (1);
}


int expand_heredoc_digit_variable (char *line, char **xline, int *i)
{
	if (line[*i] == '0')
	{
		*xline = adapted_strjoin(*xline, "✌️ bash");
		if (!*xline)
			return (0);
		(*i)++;
	}
	else 
	{
		*xline = adapted_strjoin(*xline, "");
		if (!*xline)
			return (0);
		(*i)++;
	}
	return (1);
}



int there_is_heredoc_expansion_to_manage (char *line,  int *i, char **xline, t_general *data)
{
	if (line[*i] && (ft_isalpha(line[*i]) == 1 || line[*i] == '_'))
	{
		if (expand_heredoc_regular_variable (line, i, data->env_lst, xline) == 0)
			return (0);
	}
	else if (line[*i] && line[*i] == '?')
	{
		if (expand_heredoc_exit_status_variable(data->exit_status, xline, i) == 0)
			return (0);
	}
	else if (line[*i] && ft_isdigit(line[*i]) == 1)
	{
		if (expand_heredoc_digit_variable (line, xline, i) == 0)
			return (0);
	}
	return (1);
}


char *expand_line (char *line, t_general *data)
{
	char *xline;
	int i;
	
	i = 0;
	xline = NULL;
	printf("#Expand heredoc line:\n");
	while (line[i])
	{
		if(line[i] == '$')
		{
			i++;
			if (there_is_heredoc_expansion_to_manage (line, &i, &xline, data) == 0)
				return (0);		
			printf("   Contenido de xline: %s\n", xline);
			
			continue ;
		}	

		xline = strjoinchar (xline, line[i]);
		if (!xline)
			return (0);
		i++;
	}
	printf("**************Contenido de xline final: %s\n", xline);
	return (xline);
}
