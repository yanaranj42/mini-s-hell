/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/19 08:23:46 by mfontser         ###   ########.fr       */
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
	char *line;
	char **own_env;
	char *pretoken;
	t_quotes qdata; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_token *first_token; 
}	t_general;

//creo la variable como tal vs un puntero, pero la variable me faltaria crearla en la funcion que toque, no?


int		get_own_env(char **env, t_general *data);
int 	env_matrix_base (char **env);
void	perror_message(char *start, char *message);

//INITIALITATIONS
void 	init_data_values(t_general *data);
void	init_quote_values(t_general *data); 

//LEXER
int 	lexer (t_general *data);
void 	delete_spaces (t_general *data);
int 	review_closed_quotes (t_general *data);
int 	delete_useless_spaces (t_general *data);

//PARSER
int 	parser(t_general *data);
int 	take_pretoken (t_general *data, int *i);
t_token	*create_token (t_general *data);
void 	put_new_list_node (t_general *data, t_token *new_token);
t_token *create_token_content (t_general *data, t_token *new_token);
void 	debug_token(t_token *token, int num);
char	**ft_token_split(char const *s, char del, t_general *data);

	//UTILS
	char 	*strjoinchar (char *str, char c); //IRA EN LIBFT, BORRAR LUEGO DE AQUI
	void 	account_quotes (char c, t_general *data); //revisar si hay que reubicar
	
//EXECUTOR
void 	print_env(t_general *data);
int 	pseudoexecutor(t_general *data);

//FREE
void	free_env(t_general *data);
void	free_before_end(t_general *data);
void 	free_tokens_list(t_general *data);


#endif