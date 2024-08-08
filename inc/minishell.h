/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 01:43:37 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
	char **argv;
	int argc;
	struct s_token *back;
	struct s_token *next;
}	t_token;

typedef struct s_general
{
	char **own_env;
	t_token *first_token;
}	t_general;


int		get_own_env(char **env, t_general *data);
int 	env_matrix_base (char **env);
void	free_env(t_general *data);
void	perror_message(char *start, char *message);
void 	init_data_values(t_general *data); 

void 	pseudoparser(char *line, t_general *data);
void 	debug_token(t_token *token);

void 	print_env(t_general *data);


void	free_before_end(t_general *data);


#endif