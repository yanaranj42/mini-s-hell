/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:40:28 by mfontser          #+#    #+#             */
/*   Updated: 2024/11/06 16:20:44 by mfontser         ###   ########.fr       */
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
#define ORANGE  "\e[1;38;2;255;128;0m"

/*STANDARD*/
#define STDIN	0
#define STDOUT	1
#define STDERR	2

/*ERRORS*/ // PENDIENTE BORRAR Y PONER DIRECTAMENTE LOS ERRORES EN LOS MENSAJES
#define	ERR01	"Malloc error\n"
#define ERR02	"ENV creation failiure"

/*PARSING*/
#define PIPE 1
#define INPUT 2  // < STDIN_REDIRECTION
#define HEREDOC 3 // << STDIN_DOUBLE_REDIRECTION 
#define OUTPUT 4 // > STDOUT_REDIRECTION
#define APPEND 5 // >>  STDOUT_DOUBLE_REDIRECTION
#define FILE_REDIRECTION 6
#define CMD_ARGV 7


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
	char 		*content; 
	struct 		s_token *back;
	struct 		s_token *next;
	int 		type;
	
}				t_token;			

typedef struct s_xtkn
{
	char 		*content;
	struct 		s_xtkn *back;
	struct 		s_xtkn *next;
	int 		type;
	int 		heardoc_expansion;
	
}				t_xtkn;	

typedef struct s_redir
{
	int		type;
	char	*file_name;
	int		fd; // Esto lo necesito para los heredocs
	int 	heardoc_expansion;
	struct 	s_redir	*next;
} 			t_redir;


typedef struct s_cmd
{
	char		**argv;
 	char		*path;
	pid_t		pid;
	t_redir		*first_redir;
	struct 		s_cmd *next;
	int		fd_in; // para las redirs de input
	int		fd_out; // para las redirs de output
//(se van actualizando prq los voy sobreescribiendo)
	

}				t_cmd;



typedef struct s_general
{
	// int			ret_exit;//variable yaja
	int			flag; 	 //variable yaja
	t_env		*env_lst;//variable yaja
	int			equal;  //variable yaja
	int			builtin; //variable yaja

	char 		*line;
	char 		*pretoken;
	t_quotes	qdata; //DIFERENCIA ENTRE HACERLO PUNTERO O NO, TENIA DUDA CON LAS QUOTES.
	t_token		*first_token; 
	t_xtkn		*first_xtkn; 

	char		**paths;
	char 		**env_matrix;
	t_cmd		*first_cmd;
	int 		exit_status;
	int			pipe_fd[2];
	int 		next_cmd_input_fd;
}				t_general;



//INITIALITATIONS
void 	init_data_values(t_general *data);
void	init_quote_values(t_general *data); 

//CREATE OWN ENVIROMENT
int		get_own_env(t_general *data, char **env);
void	env_to_lst(t_general *data, t_env *new_env);

//LEXER
int 	lexer (t_general *data);
void 	delete_spaces (t_general *data);
int 	fill_updated_line (t_general *data);
int 	review_closed_quotes (t_general *data);
int 	delete_useless_spaces (t_general *data);


//PARSER
int 	parser(t_general *data);
int		prepare_pretoken(t_general *data, int *i, char ***argv);
int 	take_pretoken (t_general *data, int *i);
int		fill_separator_pretoken(t_general *data, int *i);
int		fill_word_pretoken(t_general *data, int *i);
int		is_real_separator(char c, t_general *data);
int		build_tokens_list(t_general *data, char ***argv);
t_token	*create_token (t_general *data);
void 	put_new_list_node (t_general *data, t_token *new_token);
void 	classify_token_type (t_token *new_token);
int 	check_syntax_errors (t_general *data);
int		check_syntax_errors_2(t_general *data, t_token *tmp_token);
void	check_number_of_heredocs(t_general *data);
int 	check_pipe (t_general *data, t_token *token);
int 	check_input (t_general *data, t_token *token);
int 	check_heredoc (t_general *data, t_token *token);
int 	check_output (t_general *data, t_token *token);
int 	check_append (t_general *data, t_token *token);

//UTILS
char	**ft_token_split(char const *s, char del, t_general *data);



//EXPANSOR
int 	expansor(t_general *data);
int 	start_xtkns (t_general *data);
t_xtkn *expand_xtkn(t_token *token, t_general *data);
t_xtkn *token_to_xtoken(t_token *token, t_general *data);
t_xtkn *create_xtoken (void);
void 	put_new_list_xtoken_node (t_general *data, t_xtkn *xtkn);
int 	build_expanded_content (t_xtkn *xtkn, t_token *token, t_general *data);
int 	there_is_expansion_to_manage (t_xtkn *xtkn, t_token *token, int * i, t_general *data);
int 	there_is_expansion_to_manage_2 (t_xtkn *xtkn, t_token *token, int * i, t_general *data);
int 	expand_regular_variable(t_token *token, t_xtkn	*xtkn, int * i, t_general *data);
char 	*identify_variable_to_expand (t_token *token, int *i);
int 	miniquotes_conversion (t_xtkn	*xtkn, char *tmp);
int 	quotes_conversion (t_xtkn *xtkn, char *tmp, t_env *env);
int 	build_heredoc_delimiter (t_xtkn	*xtkn, char *tmp);
int 	manage_quotes_variable (t_xtkn	*xtkn, char *tmp, t_env *env);
int 	regular_conversion (t_token *token, t_xtkn	*xtkn, char *tmp,  t_env *env, int *i);
int 	manage_inexistent_regular_variable (t_xtkn	*xtkn, t_token *token, char *tmp, int *i);
int 	manage_regular_variable (t_xtkn	*xtkn, t_token *token, char *tmp, t_env *env);
int 	expansor_variable_has_space (char *tmp, t_env *env);
int 	expand_exit_status_variable (t_xtkn	*xtkn, int exit_status, int *i);
int 	expand_digit_variable (t_general *data, t_token *token, t_xtkn	*xtkn, int *i);
int 	manage_quotes_after_dollar (t_general *data, t_token *token, t_xtkn	*xtkn, int *i);
int 	manage_miniquotes_after_dollar (t_general *data, t_token *token, t_xtkn	*xtkn, int *i);
int 	manage_dollar_variable_between_quotes (t_general *data, t_token *token, t_xtkn	*xtkn, int *i);
int 	check_expansor_variable_exists (char *tmp, t_env *env);
int 	change_expansor_variable(t_xtkn *xtkn, char *tmp, t_env *env);
int 	expand_final_value (t_xtkn *xtkn, t_env *env_tmp, int *i);
int 	split_xtkn(t_xtkn	*xtkn, t_general *data);
int 	retokenize_same_xtoken (t_xtkn	*xtkn, char **splited_content);
int 	enlarge_xtkns_list (t_xtkn	*xtkn, t_general *data, int *i, char **splited_content, t_xtkn	*new_xtkn);
int 	finish_xtkns (t_xtkn *first_xtkn, t_general *data);
int 	remove_quotes(t_xtkn *xtkn, t_general *data);
int 	build_content_without_quotes (t_xtkn *xtkn, t_general *data, char **tmp);
void 	change_non_printable_chars(t_xtkn *xtkn);


//EXECUTOR
int 	executor (t_general *data);
int		get_matrix_env(t_general *data, t_env *env_lst);
int 	env_matrix_base (t_env *env_lst);
int 	fill_matrix (t_env *tmp, t_general *data, int *i);
int		get_all_paths(t_env	*env_lst, t_general *data);
t_env 	*there_is_path(t_env *env_lst);
int 	get_command (t_general *data, t_xtkn *first_xtkn);


int 	do_heredoc(t_general *data);


char 	*expand_line (char *line, t_general *data);
int 	get_children(t_general *data);
int 	count_commands(t_general *data);
int		create_child(t_general *data, t_cmd *cmd, int i, int n);
void	check_cmd(t_cmd *cmd, char **paths);
char	*check_cmd_access(char **paths, char *cmd_argv);
char 	*check_cmd_current_directory(char *cmd_argv);
char	*check_cmd_absolut_path(char *cmd_argv);
char	*check_cmd_relative_path(char *cmd_argv, char *path);
void	execute_builtin(t_general *data, t_cmd *cmd);
int		is_builtin(t_cmd *cmd);
int check_father_redirs (t_general *data,t_cmd *first_cmd);
void	father_status(t_general *data);




	//BUILT-INS
	void 	pseudoexecutor(t_general *data, t_cmd *cmd);
	int		is_builtin(t_cmd *cmd);
	
	int		ft_env(t_env *env);
	int		ft_pwd(void);
	
	int		ft_cd(t_general *data);
	int		go_to_path(int opt, t_general *data);
	int		update_pwd(t_general *data);
	int		env_update(t_env *head, char *k_word, char *n_value);
	char	*get_env_path(t_general *data, char *k_word);

	int		ft_echo(char **argv);
	void	ft_exit(t_general *data);
	
	int		ft_export(t_general *data);
	int		handle_args(t_general *data, char *argv);
	/*export utils*/
	void	print_env(t_general *data, t_env *tmp);//MODIFF
	void	print_sort(t_env *own_env);
	int		print_export_lst(t_general *data, t_env *own_env);//inicia con la flag en 1
	int		export_opt(char *name, char *argv);
	void	export_plus_var(t_general *data, char *name, char *value);
	char	*find_env_var(t_general *data, char *var_name);
	int		env_add_last(t_general *data, char *name, char *value);
	void	add_upd_env(t_general *data, char *name, char *value);


//UTILS
void 	account_quotes (char c, t_general *data);

//ERROR_MESSAGES
void	perror_message(char *start, char *message);
void 	ambiguous_redirect (char *start);
void	unexpected_token_message(char *message);
void	command_not_found(char *start);
void	permission_denied(char *start);
void	no_such_file_or_directory(char *start);
void maximum_heredoc_exceeded (void);
//ERROR BUILTINS
int		error_opt(char *s1, char *s2, char **arr, char *argv);
void	error_brk(t_general *data, char *msg, char *name, int flag);

//FREE
char	**arr_clean(char **arr);
void	*ft_memdel(void *ptr);
void	unset_free(t_env *env);
void	free_exit(t_general *data);
void	free_data_paths (t_general *data);
void	free_env(t_env *head);
void 	free_splited_content (char **content);
void	free_before_end(t_general *data);
void 	free_tokens_list(t_general *data);
void 	free_xtkns_list(t_general *data);
void 	free_pretoken_argv (char ***argv);
void	free_matrix_env(t_general *data);
void 	free_cmd(t_general *data);
void 	free_expansor_splited_content (char **splited_content);
void free_expansor (t_general *data);
void free_parsing_process (t_general *data, char ***argv);
void	free_get_cmd_process(t_general *data);
void free_executor_process (t_general *data);


#endif