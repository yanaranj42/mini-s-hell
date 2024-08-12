/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/12 15:51:54 by yanaranj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

/* COLORS*/
#define END		"\x1b[0m"
#define RED		"\x1b[31m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"

/*ERRORS*/
#define	ERR01	"Malloc error\n"
#define ERR02	RED"ENV creation failiure"END

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

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_general
{
	t_env		*env_lst;
	t_token *first_token; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_quotes qdata; 
}	t_general;

//creo la variable como tal vs un puntero, pero la variable me faltaria crearla en la funcion que toque, no?
//built-ins
//			--OWN_ENVIRONMENT.C--				//
int		get_own_env(t_general *data, char **env);
void	env_to_lst(t_general *data, t_env *new_env);
int		ft_env(t_env *env);

//			--INITIALIZATIONS.C--				//
int 	init_values(t_general *data, char **env);
void	init_quote_values(t_general *data); 

//				--FREE.C--				//
void	free_env(t_env *head);
void 	free_tokens_list(t_token *token);
void 	free_token(t_token *token);
void	free_before_end(t_general *data);

void	perror_message(char *start, char *message);
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


#endif
