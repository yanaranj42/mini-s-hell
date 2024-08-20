/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/20 12:25:24 by yanaranj         ###   ########.fr       */
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
# include <limits.h>

/* COLORS*/
#define END		"\x1b[0m"
#define RED		"\x1b[31m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define GREEN	"\x1b[32m"

/*ERRORS*/
#define	ERR01	"Malloc error\n"
#define ERR02	"ENV creation failiure"
#define STDERR	2
#define FAIL	0
#define SUCCESS	1
#define OTHER	3 //tmp

/*OTROS
#define LONG_MIN "-9223372036854775807"
#define LONG_MAX "9223372036854775807"*/

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
	int			ret_exit;
	int			flag;
	t_env		*env_lst;
	t_token *first_token; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_quotes qdata;
}	t_general;

//creo la variable como tal vs un puntero, pero la variable me faltaria crearla en la funcion que toque, no?

//				**built-ins**					//
int		ft_env(t_env *env);
int		ft_pwd(void);
int		ft_cd(t_general *data);
int		ft_echo(char **argv);

//				**EXIT.C**					//
void	ft_exit(t_general *data);
void	cases(t_general *data);


//					**lexer**					//
int		lexer (char **line, t_general *data);
void	delete_spaces (char **line);
int		review_quotes (char **line, t_general *data);

//					**parser**					//
void	pseudoparser(char *line, t_general *data);
void	debug_token(t_token *token);

//					**executor**				//
void	print_env(t_general *data);
int		pseudoexecutor(t_general *data);

//			--OWN_ENVIRONMENT.C--				//
int		get_own_env(t_general *data, char **env);
void	env_to_lst(t_general *data, t_env *new_env);

//					--CD.C--					//
int		ft_cd(t_general *data);
int		go_to_path(int opt, t_general *data);
int		update_pwd(t_general *data);
int		env_update(t_env *head, char *k_word, char *n_value);
char	*get_env_path(t_general *data, char *k_word);

//			--INITIALIZATIONS.C--				//
int		init_values(t_general *data, char **env);
void	init_quote_values(t_general *data); 

//					--FREE.C--					//
void	free_env(t_env *head);
void	free_tokens_list(t_token *token);
void	free_token(t_token *token);
void	free_before_end(t_general *data);

//				--ERROR_MESSAGES.C--			//
void	perror_message(char *start, char *message);

#endif