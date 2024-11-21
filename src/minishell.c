/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:00:25 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/20 20:49:47 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	line_is_empty_or_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	minishell_loop(t_general *data)
{
	init_non_bloquing_signals();
	data->line = readline("🔥 ÐrackyŠhell ▶ ");
	if (!data->line)
		do_eof();
	init_ignore_signals();
	if (g_error != 0)
		data->exit_status = g_error;
	if (!line_is_empty_or_whitespace(data->line))
		add_history(data->line);
	if (lexer(data) == 0)
		return (free(data->line), 0);
	if (parser(data) == 0 || check_syntax_errors(data) == 0)
		return (free(data->line), 0);
	if (expansor(data) == 0)
		return (free(data->line), 0);
	if (executor(data) == 0)
		return (free(data->line), 0);
	free_before_next_round(data);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_general	data;

	(void)argv;
	if (argc != 1)
	{
		too_many_parameters();
		return (1);
	}
	init_data_values(&data);
	if (get_own_env(&data, env) == 0)
		return (1);
	while (1)
	{
		if (minishell_loop(&data) == 0)
			continue ;
	}
	free_env(data.env_lst);
	return (0);
}
