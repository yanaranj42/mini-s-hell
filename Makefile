# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yanaranj <yanaranj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2024/10/15 12:19:06 by yanaranj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------COLORS------------------------------------------------------#

NC = \033[0m
GREEN = \033[1;92m
RED = \033[1;91m
#YELLOW = \033[1;33m
YELLOW = \e[1;93m

#------------------------------------------------VARIABLES---------------------------------------------------#

FILES = minishell.c initializations.c error_messages.c lexer_parser_utils.c free.c

FILES += own_env/own_enviroment.c

FILES += lexer/lexer.c

FILES += signals/signals.c 

FILES += parser/parser.c parser/ft_token_split.c parser/check_syntax_errors.c

FILES += expansor/expansor.c

FILES += executor/executor.c executor/matrix_enviroment.c executor/get_env_paths.c executor/child_utils.c executor/father_status.c


FILES += built-ins/builtins.c built-ins/env.c built-ins/echo.c built-ins/cd.c built-ins/pwd.c built-ins/exit.c built-ins/export.c built-ins/export_utils.c built-ins/export_utils2.c 


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

LIBS = libs/Libft/libft.a -ldl -lglfw -lm

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
	@echo "$(END)"

clean:
	@${RM} ${OBJDIR}
	@make -C libs/Libft clean
	@echo "$(RED)DRACKYSHELL OBJECTS DELETED$(END)"

fclean:
	@${RM} ${OBJDIR}
	@echo "$(RED)DRACKYSHELL OBJECTS DELETED$(END)"
	@${RM} ${NAME}
	@make -C libs/Libft fclean
	@echo "$(RED) DRACKYSHELL EXEC DELETED$(END)"

re: fclean all
#	@echo "drackishell re done"

.PHONY: all clean fclean re