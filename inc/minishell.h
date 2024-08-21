/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/08/21 23:10:45 by mfontser         ###   ########.fr       */
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
	char 		**argv;
	int 		argc;
	struct 		s_token *back;
	struct 		s_token *next;
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
	char 		**own_env;
	char 		*pretoken;
	t_quotes	qdata; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_token		*first_token; 
}				t_general;

//creo la variable como tal vs un puntero, pero la variable me faltaria crearla en la funcion que toque, no?





//CREATE OWN ENVIROMENT
int		get_own_env(char **env, t_general *data);
int 	env_matrix_base (char **env);


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

	//BUILT-INS
	int		ft_env(t_env *env);
	int		ft_pwd(void);
		// CD
		int		ft_cd(t_general *data);
		int		go_to_path(int opt, t_general *data);
		int		update_pwd(t_general *data);
		int		env_update(t_env *head, char *k_word, char *n_value);
		char	*get_env_path(t_general *data, char *k_word);

	int		ft_echo(char **argv);
	void	ft_exit(t_general *data);
	//void	cases(t_general *data);


//ERROR_MESSAGES
void	perror_message(char *start, char *message);

//FREE
void	free_env(t_general *data);
void	free_before_end(t_general *data);
void 	free_tokens_list(t_general *data);


#endif