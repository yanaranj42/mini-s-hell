/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/09/11 21:08:25 by mfontser         ###   ########.fr       */
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
# include <sys/wait.h>
# include <fcntl.h>


/*COLORS*/
#define END		"\x1b[0m"
#define RED		"\e[1;91m"
#define YELLOW	"\e[1;93m"
#define BLUE	"\e[1;94m"
#define GREEN	"\e[1;92m"
#define CYAN	"\e[1;96m"
#define PURPLE 	"\e[1;95m"

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
#define FILE 6
#define CMD 7



/*OTROS
#define LONG_MIN "-9223372036854775807"
#define LONG_MAX "9223372036854775807"*/


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

typedef struct s_token
{
	//char 		**argv;
	//int 		argc;
	char 		*content;
	struct 		s_token *back;
	struct 		s_token *next;
	int 		type;
	char		*path;
	
}				t_token;			

typedef struct s_cmd
{
	char		**argv;
 	char		*path;
	pid_t		pid;
//	int		fd_in; // para las redirs de input
//	int		fd_out; // para las redirs de output
//(se van actualizando prq los voy sobreescribiendo)
	t_redir		*first_redir;
	int			indx; // cuál comando es
	struct 		s_cmd *next;
}			t_cmd;


typedef struct s_redir
{
	t_type	type;
	char	*file_name;
	//int		fd; // Esto se necesitara para los heredocs, pero ya vere donde lo necesito y de donde lo saco
	struct s_redir		*next;
} 	t_redir;





typedef struct s_general
{
	int			ret_exit;//variable yaja
	int			flag; 	 //variable yaja
	t_env		*env_lst;//variable yaja

	char 		*line;
	char 		*pretoken;
	t_quotes	qdata; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_token		*first_token; 
	char		**paths;
	char 		**env_matrix;
	t_cmd		*first_cmd;
	int 		exit_status;
	int			pipe_fd[2];
	int 		reading_pipe_fd;



}				t_general;


// | | -> error 2
// g_exit_status = 2;
// readline drakishell: $? // en la fase de expansor sustituyo $? por el valor de g_exit_status, osea 2 en este caso.
// despues de expansor , viene ejecutor, que estoy ejecutando , un token que antes tenia argv[0] -> $? pero ahora es argv[0] -> 2
//por lo tanto lo que estoy ejecutando es como si directamente hubiera puesto un 2

// | | -> error 2
// g_exit_status = 2;
// echo $?
// En el expansor me queda echo 2, porque se ha expandido al valor de g_exit_status y me imprime el 2 que le he pedido con el echo




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
//t_token *create_token_content (t_general *data, t_token *new_token);
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
//int 	pseudoexecutor(t_general *data);
int 	executor (t_general *data);
int		get_matrix_env(t_general *data, t_env *env_lst);
int 	env_matrix_base (t_env *env_lst);
void 	print_matrix_env(char **matrix_env); //borrar
int		get_all_paths(t_env	*env_lst, t_general *data);
t_env 	*there_is_path(t_env	*env_lst);

int 	get_children(t_general *data);
int 	count_commands(t_general *data);
int		create_child(t_general *data, t_token *tkn);
void	check_cmd(t_token *cmd, char **paths);
char	*check_cmd_access(char **paths, char *cmd_argv);
char 	*check_cmd_current_directory(char *cmd_argv);
char	*check_cmd_absolut_path(char *cmd_argv);
char	*check_cmd_relative_path(char *cmd_argv, char *path);
void	father_status(t_general *data);




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
void	command_not_found(char *start);
void	permission_denied(char *start);
void	no_such_file_or_directory(char *start);

//FREE
void	free_exit(t_general *data);
void	free_data_paths (char **paths);
void	free_env(t_env *head);
void	free_before_end(t_general *data);
void 	free_tokens_list(t_general *data);
void 	free_pretoken_argv (char **argv);
void	free_matrix_env(t_general *data);


#endif