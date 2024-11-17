/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tokens_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 20:05:27 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/12 04:57:55 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	classify_token_type(t_token *new_token)
{
	if (ft_strncmp("|", new_token->content, 2) == 0)
		new_token->type = PIPE;
	else if (ft_strncmp("<", new_token->content, 2) == 0)
		new_token->type = INPUT;
	else if (ft_strncmp("<<", new_token->content, 3) == 0)
		new_token->type = HEREDOC;
	else if (ft_strncmp(">", new_token->content, 2) == 0)
		new_token->type = OUTPUT;
	else if (ft_strncmp(">>", new_token->content, 3) == 0)
		new_token->type = APPEND;
	else if (new_token->back && (new_token->back->type == INPUT
			|| new_token->back->type == HEREDOC
			|| new_token->back->type == OUTPUT
			|| new_token->back->type == APPEND))
		new_token->type = FILE_REDIRECTION;
	else
		new_token->type = CMD_ARGV;
}

void	put_new_list_token_node(t_general *data, t_token *new_token)
{
	t_token	*tmp_token;

	if (!data->first_token)
	{
		data->first_token = new_token;
		data->first_token->back = NULL;
		data->first_token->next = NULL;
	}
	else
	{
		tmp_token = data->first_token;
		while (tmp_token && tmp_token->next)
			tmp_token = tmp_token->next;
		tmp_token->next = new_token;
		new_token->back = tmp_token;
		new_token->next = NULL;
	}
}

t_token	*create_token(t_general *data)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token) * 1);
	if (!new_token)
	{
		printf("Error: New token malloc fail\n");
		free(data->pretoken);
		free_tokens_list(data);
		return (NULL);
	}
	return (new_token);
}
/*
int	build_tokens_list(t_general *data, char ***argv)
{
	int		j;
	t_token	*new_token;
	char	**tmp;

	tmp = *argv;
	j = 0;
	printf ("puntero: %p\n", &argv[j]);
	printf ("puntero contenido: %s\n", *argv[j]);
	while (*argv[j])
	{
		printf("vuelta-> %d\n", j);
		new_token = create_token(data);
		if (!new_token)
		{
				printf("A2A\n");
			free_parsing_process(data, argv);
			return (0);
		}
		put_new_list_token_node(data, new_token);
		printf("A1A\n");
		new_token->content = strdup(*argv[j]);
		printf("ABA\n");
		if (!new_token->content)
		{
				printf("A3A\n");
			free_parsing_process(data, argv);
			return (0);
		}
		classify_token_type(new_token);
		j++;
	printf ("puntero: %p\n", &argv[j]);
	printf ("puntero contenido: %s\n", *argv[j]);
	}
	return (1);
}
*/

int	build_tokens_list(t_general *data, char ***argv)
{
	int		j;
	t_token	*new_token;
	char	**tmp;

	tmp = *argv;
	j = 0;
	while (tmp[j])
	{
		new_token = create_token(data);
		if (!new_token)
		{
			free_parsing_process(data, argv);
			return (0);
		}
		put_new_list_token_node(data, new_token);
		new_token->content = strdup(tmp[j]);
		if (!new_token->content)
		{
			free_parsing_process(data, argv);
			return (0);
		}
		classify_token_type(new_token);
		j++;
	}
	return (1);
}
