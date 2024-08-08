# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2024/08/08 14:08:29 by mfontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#------------------------------------------------COLORS------------------------------------------------------#
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW= \033[1;33m

#------------------------------------------------VARIABLES---------------------------------------------------#

FILES = minishell.c initializations.c own_enviroment.c error_messages.c free.c

FILES += built-ins/env.c 

FILES += lexer/lexer.c 

FILES += parser/pseudoparser.c 

FILES += executor/pseudoexecutor.c 

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
	@echo "$(GREEN)DRACKYSHELL DONE$(END)"
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
