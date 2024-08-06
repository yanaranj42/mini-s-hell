# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfontser <mfontser@student.42.barcel>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 12:21:16 by mfontser          #+#    #+#              #
#    Updated: 2024/08/06 12:59:45 by mfontser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#------------------------------------------------VARIABLES---------------------------------------------------#

FILES = minishell.c

SRCDIR = src/
SRCS = 	$(addprefix $(SRCDIR), $(FILES))

OBJDIR = obj/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

INCLUDES = -I ./libs/Libft -I ./inc

NAME = minishell

HEADER = inc/minishell.h
CC = cc 
RM = rm -rf 
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
LDFLAGS = -lreadline

LIBS = libs/Libft/libft.a -ldl -lglfw -lm

#--------------------------------------------------NORMAS----------------------------------------------------#

#Metodo implicito

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADER) Makefile libs/Libft/libft.a  
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Mis metodos

all: make_libs ${NAME}

make_libs:
	make -C libs/Libft all

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} $(LIBS) -o $(NAME) $(LDFLAGS)

clean:
	${RM} ${OBJDIR}
	make -C libs/Libft clean

fclean:
	${RM} ${OBJDIR}
	${RM} ${NAME} 
	make -C libs/Libft fclean

re: fclean all
	@echo "re done"

.PHONY: all clean fclean re
