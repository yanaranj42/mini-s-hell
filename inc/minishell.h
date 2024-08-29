/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/29 14:01:30 by mfontser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

/*COLORS*/
#define END		"\x1b[0m"
#define RED		"\e[1;91m"
#define YELLOW	"\e[1;93m"
#define BLUE	"\e[1;94m"
#define GREEN	"\e[1;92m"
#define CYAN	"\e[1;96m"

//De donde son los codigos de estos colores? Porque son distintos de los del makefile???
//Propongo esos codigos nuevos que creo que en tu terminal se ven igual y en la mia se ven vivos también
//Codigos viejos por si acaso:
/*
#define END		"\x1b[0m"
#define RED		"\x1b[31m"
#define YELLOW	"\x1b[33m"
#define BLUE	"\x1b[34m"
#define GREEN	"\x1b[32m"
#define CYAN	"\x1b[36m"
*/

/*ERRORS*/
#define	ERR01	"Malloc error\n"
#define ERR02	"ENV creation failiure"
#define STDERR	2


#define STDIN	0
#define STDOUT	1
#define STDERR	2


/*PARSING*/
#define PIPE 1
#define STDIN_REDIRECTION 2
#define STDIN_DOUBLE_REDIRECTION 3
#define STDOUT_REDIRECTION 4
#define STDOUT_DOUBLE_REDIRECTION 5
#define NO_SEPARATOR 6


/*OTROS
#define LONG_MIN "-9223372036854775807"
#define LONG_MAX "9223372036854775807"*/



typedef struct s_token
{
	char 		**argv;
	int 		argc;
	struct 		s_token *back;
	struct 		s_token *next;
	int 		type;
}				t_token;


typedef struct s_quotes
{
	int 	quotes;
	int 	miniquotes;
}			t_quotes;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;


typedef struct s_general
{
	int			ret_exit;//variable yaja
	int			flag; 	 //variable yaja
	t_env		*env_lst;//variable yaja

	char 		*line;
	char 		*pretoken;
	t_quotes	qdata; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_token		*first_token; 
	
}				t_general;

//creo la variable como tal vs un puntero, pero la variable me faltaria crearla en la funcion que toque, no?





//CREATE OWN ENVIROMENT
int		get_own_env(t_general *data, char **env);
void	env_to_lst(t_general *data, t_env *new_env);


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
int 	is_real_separator(char c, t_general *data);
int 	take_pretoken (t_general *data, int *i);
t_token	*create_token (t_general *data);
void 	put_new_list_node (t_general *data, t_token *new_token);
t_token *create_token_content (t_general *data, t_token *new_token);
void 	classify_token_type (t_token *new_token);
void 	debug_token(t_token *token, int num); // BORRAR
char	**ft_token_split(char const *s, char del, t_general *data);

	//UTILS
	char 	*strjoinchar (char *str, char c); //IRA EN LIBFT, BORRAR LUEGO DE AQUI
	void 	account_quotes (char c, t_general *data); //revisar si hay que reubicar

int 	check_syntax_errors (t_general *data);
int 	check_pipe (t_general *data, t_token *token);
int 	check_stdin_redirection (t_general *data, t_token *token);
int 	check_stdin_double_redirection (t_general *data, t_token *token);
int 	check_stdout_redirection (t_general *data, t_token *token);
int 	check_stdout_double_redirection (t_general *data, t_token *token);


//EXECUTOR
int 	pseudoexecutor(t_general *data);


	//BUILT-INS
	int		ft_env(t_env *env);
	int		ft_pwd(void);
	
	int		ft_cd(t_general *data);
	int		go_to_path(int opt, t_general *data);
	int		update_pwd(t_general *data);
	int		env_update(t_env *head, char *k_word, char *n_value);
	char	*get_env_path(t_general *data, char *k_word);

	int		ft_echo(char **argv);
	void	ft_exit(t_general *data);


//ERROR_MESSAGES
void	perror_message(char *start, char *message);
void	unexpected_token_message(char *message);

//FREE
void	free_exit(t_general *data);
void	free_env(t_env *head);
void	free_before_end(t_general *data);
void 	free_tokens_list(t_general *data);


#endif