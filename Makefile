# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    template_Makefile                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 09:56:12 by sravizza          #+#    #+#              #
#    Updated: 2025/02/21 16:14:08 by sravizza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##								DIRECTORIES									  ##
SRC_DIR		=	src
OBJ_DIR		=	obj
INCL_DIR	=	include

################################################################################
##								  SOURCES									  ##

SRC			=	cleanup.c	init.c	main.c	monitor.c	parsing.c	routine.c  \
				utils.c

################################################################################
##								 ARGUMENTS									  ##


NAME		= 	philo
CC			= 	gcc
CFLAGS		= 	-Wall -Werror -Wextra -I$(INCL_DIR)
OBJ			= 	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
RM			= 	rm -f
AR			= 	ar -rcs


################################################################################
##								   RULES									  ##

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	echo $(NAME) "compiled"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

################################################################################
##								   COMMANDS									  ##

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	echo $(NAME) "obj removed"

fclean: clean
	$(RM) $(NAME)
	echo $(NAME) "removed"

re: clean all

debug: CFLAGS += -g
debug: re
	echo $(NAME) "compiled in debug mode"

valgrind: re
	valgrind --leak-check=full ./$(NAME)

.SILENT:

.PHONY: all clean fclean re debug