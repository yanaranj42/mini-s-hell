/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/08 23:09:25 by mfontser         ###   ########.fr       */
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

typedef struct s_quotes
{
	int quotes;
	int miniquotes;
}	t_quotes;

typedef struct s_general
{
	char **own_env;
	t_token *first_token; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_quotes qdata; 
}	t_general;

//creo la variable como tal vs un puntero, pero la variable me faltaria crearla en la funcion que toque, no?


int		get_own_env(char **env, t_general *data);
int 	env_matrix_base (char **env);
void	free_env(t_general *data);
void	perror_message(char *start, char *message);
void 	init_data_values(t_general *data);
void	init_quote_values(t_general *data); 

//LEXER
int 	lexer (char **line, t_general *data);
void 	delete_spaces (char **line);
int 	review_quotes (char **line, t_general *data);

//PARSER
void 	pseudoparser(char *line, t_general *data);
void 	debug_token(t_token *token);

//EXECUTOR
void 	print_env(t_general *data);
int 	pseudoexecutor(t_general *data);

void 	free_tokens_list(t_token *token);
void 	free_token(t_token *token);
void	free_before_end(t_general *data);


#endif