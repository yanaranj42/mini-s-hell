# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2024/11/21 16:36:56 by mfontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------COLORS------------------------------------------------------#

NC = \033[0m
GREEN = \033[1;92m
RED = \033[1;91m
YELLOW = \e[1;93m

#------------------------------------------------VARIABLES---------------------------------------------------#

FILES =  minishell.c

FILES += utils/general_utils.c utils/ft_token_split.c utils/split_utils.c

FILES += initializations/initializations.c

FILES += signals/init_signals.c signals/control_c_handler.c

FILES += own_env/own_enviroment.c own_env/set_empty_env.c

FILES += lexer/lexer.c 

FILES += parser/parser.c parser/prepare_pretoken.c parser/build_tokens_list.c \
		 parser/prepare_syntax_errors_checking.c parser/check_syntax_errors.c

FILES += expansor/expansor.c expansor/expand/expand_xtkn.c expansor/expand/token_to_xtoken.c \
		 expansor/expand/build_expanded_content.c expansor/expand/expand_regular_variable.c \
		 expansor/expand/miniquotes_conversion.c expansor/expand/quotes_conversion.c \
		 expansor/expand/regular_conversion.c expansor/expand/expand_special_variables.c \
		 expansor/expand/check_expansor_variable_exists.c expansor/expand/change_expansor_variable.c \
		 expansor/split/split_xtkn.c expansor/quotes/finish_xtkns.c

FILES += executor/executor.c executor/preparations_for_the_executor/preparations_for_the_executor.c \
		 executor/preparations_for_the_executor/get_matrix_enviroment.c executor/preparations_for_the_executor/get_env_paths.c \
		 executor/preparations_for_the_executor/get_command/get_command.c executor/preparations_for_the_executor/get_command/new_cmd_node.c \
		 executor/preparations_for_the_executor/get_command/count_cmd_argvs.c executor/preparations_for_the_executor/get_command/fill_cmd_argvs.c \
		 executor/preparations_for_the_executor/get_command/fill_cmd_redirs.c executor/do_heredoc/do_heredoc.c \
		 executor/do_heredoc/heredoc_children_process.c executor/do_heredoc/heredoc_father_status.c executor/do_heredoc/heredoc_expansion.c \
		 executor/do_heredoc/expand_specific_variables.c executor/do_execution/do_execution.c executor/do_execution/builtin_execution_only.c \
		 executor/do_execution/check_father_input_redirs.c executor/do_execution/check_father_output_redirs.c \
		 executor/do_execution/get_children.c executor/do_execution/create_child.c executor/do_execution/check_cmd_path.c \
		 executor/do_execution/check_cmd_access.c executor/do_execution/check_input_redirs.c \
		 executor/do_execution/check_output_redirs.c executor/do_execution/execute_cmd_execve.c executor/do_execution/father_status.c 

FILES += built-ins/builtins.c built-ins/env.c built-ins/echo.c built-ins/cd.c built-ins/cd_utils.c built-ins/pwd.c built-ins/exit.c \
		 built-ins/export.c built-ins/export_utils.c built-ins/export_utils2.c built-ins/unset.c


FILES += error_messages/initial_error_messages.c error_messages/parser_error_messages.c error_messages/heredoc_error_messages.c \
		 error_messages/executor_error_messages.c error_messages/builtins_error_messages.c

FILES += free/free_main.c free/free_parser.c free/free_expansor.c free/free_executor.c free/free_executor_cmd.c \
		 free/free_executor_heredoc.c free/free_builtins.c


SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

INCLUDES = -I ./libs/Libft -I ./inc

NAME = minishell

HEADER = inc/minishell.h
CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LDFLAGS = -lreadline

LIBS = libs/Libft/libft.a

#--------------------------------------------------NORMAS----------------------------------------------------#

#Metodo implicito

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) Makefile libs/Libft/libft.a  
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@)"

# Mis metodos

all: make_libs ${NAME}

make_libs:
	@make -C libs/Libft all

${NAME}: ${OBJS}
	@$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)"
	@echo " "
	@echo "                   )       \\   /      ("
	@echo "                  /|\\      )\\_/(     /|\\"
	@echo "  *              / | \\    (/\\|/\\)   / | \\             *"
	@echo "  |\`.___________/__|__o____\\\`|'/___o__|__\\__________.'|"
	@echo "  |                  '^\`    \\|/   '^\`                 |"
	@echo "  |                          V                        |"
	@echo "  |$(END)  $(RED)             🔥 DRACKYSHELL DONE 🔥 $(END) $(GREEN)            |"
	@echo "  |                                                   |"
	@echo "  | ._______________________________________________. |"
	@echo "  |'      l    /\\ /     \\\\\\\\            \\ /\\   l       \`|"
	@echo "  *       l  /   V       ))            V   \\ l        *"
	@echo "          l/            //                  \\I"
	@echo "                        V"
	@echo "$(END)$(NC)$(END)"
clean:
	@${RM} ${OBJDIR}
	@make -C libs/Libft clean
	@echo "$(RED)DRACKYSHELL OBJECTS DELETED$(END)$(NC)$(END)"

fclean:
	@${RM} ${OBJDIR}
	@echo "$(RED)DRACKYSHELL OBJECTS DELETED$(END)"
	@${RM} ${NAME}
	@make -C libs/Libft fclean
	@echo "$(RED) DRACKYSHELL EXEC DELETED$(END)$(NC)$(END)"

re: fclean all
#	@echo "drackishell re done"

.PHONY: all clean fclean re
