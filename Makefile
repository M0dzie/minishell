# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 18:51:59 by thmeyer           #+#    #+#              #
#    Updated: 2023/02/19 21:22:25 by mehdisapin       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ###################################### #
#               VARIABLES		         #
# ###################################### #

UNAME		=	$(shell uname)

NOCOLOR		=	\033[0m
BGREEN		=	\033[3;32m

NAME		=	minishell

MAKEFILE 	= 	Makefile

HEADER		=	includes/minishell.h

LIBFT_DIR	=	includes/libft/
LIBFT_A		=	$(LIBFT_DIR)libft.a

C_FLAGS		=	-Wall -Wextra -Werror
RL_FLAGS	=	-lreadline

RM			=	rm -rf

AR 			= 	ar
ARFLAGS 	= 	-rcs


# ###################################### #
#                 PATHS		             #
# ###################################### #

SRCS_PATH			=	./sources/
OBJ_DIR				=	.objs/

SRC_BUILTINS_PATH	=	$(SRCS_PATH)builtins/
SRC_CHECK_ERR_PATH	=	$(SRCS_PATH)check_errors/
SRC_ENV_VAR_PATH	=	$(SRCS_PATH)env_variables/
SRC_PARSING_PATH	=	$(SRCS_PATH)parsing/
SRC_EXECUTION_PATH	=	$(SRCS_PATH)execution/
SRC_REDIR_PATH		=	$(SRCS_PATH)redirections/
SRC_SHELL_PATH		=	$(SRCS_PATH)shell/

OBJ_BUILTINS_PATH	=	$(SRC_BUILTINS_PATH)$(OBJ_DIR)
OBJ_CHECK_ERR_PATH	=	$(SRC_CHECK_ERR_PATH)$(OBJ_DIR)
OBJ_ENV_VAR_PATH	=	$(SRC_ENV_VAR_PATH)$(OBJ_DIR)
OBJ_PARSING_PATH	=	$(SRC_PARSING_PATH)$(OBJ_DIR)
OBJ_EXECUTION_PATH	=	$(SRC_EXECUTION_PATH)$(OBJ_DIR)
OBJ_REDIR_PATH		=	$(SRC_REDIR_PATH)$(OBJ_DIR)
OBJ_SHELL_PATH		=	$(SRC_SHELL_PATH)$(OBJ_DIR)

OBJS_DIRS			=	$(OBJ_BUILTINS_PATH)	$(OBJ_CHECK_ERR_PATH)	\
						$(OBJ_ENV_VAR_PATH)		$(OBJ_PARSING_PATH)		\
						$(OBJ_EXECUTION_PATH)	$(OBJ_REDIR_PATH)		\
						$(OBJ_SHELL_PATH)


# ###################################### #
#           	  SOURCES		         #
# ###################################### #

SRC_BUILTINS_FILES	=	built_in.c

SRC_CHECK_ERR_FILES	=	

SRC_ENV_VAR_FILES	=	

SRC_PARSING_FILES	=	parsing.c parsing_quotes.c parsing_errors.c \
						parsing_redir.c parsing_echo.c 

SRC_EXECUTION_FILES	=	execution.c	pipex.c	exec_exit.c	exec_pwd.c

SRC_REDIR_FILES		=	

SRC_SHELL_FILES		=	main.c	utils.c


SRCS_BUILTINS	=	$(addprefix $(SRC_BUILTINS_PATH), $(SRC_BUILTINS_FILES))
SRCS_CHECK_ERR	=	$(addprefix $(SRC_CHECK_ERR_PATH), $(SRC_CHECK_ERR_FILES))
SRCS_ENV_VAR	=	$(addprefix $(SRC_ENV_VAR_PATH), $(SRC_ENV_VAR_FILES))
SRCS_PARSING	=	$(addprefix $(SRC_PARSING_PATH), $(SRC_PARSING_FILES))
SRCS_EXECUTION	=	$(addprefix $(SRC_EXECUTION_PATH), $(SRC_EXECUTION_FILES))
SRCS_REDIR		=	$(addprefix $(SRC_REDIR_PATH), $(SRC_REDIR_FILES))
SRCS_SHELL		=	$(addprefix $(SRC_SHELL_PATH), $(SRC_SHELL_FILES))

SRCS	=	$(SRCS_BUILTINS)	$(SRCS_CHECK_ERR)	$(SRCS_ENV_VAR)	\
			$(SRCS_PARSING)		$(SRCS_EXECUTION)	$(SRCS_REDIR)	\
			$(SRCS_SHELL)


# ###################################### #
#                OBJECTS		         #
# ###################################### #

OBJS_BUILTINS	=	$(addprefix $(OBJ_BUILTINS_PATH), 		\
					$(SRC_BUILTINS_FILES:.c=.o))

OBJS_CHECK_ERR	=	$(addprefix $(OBJ_CHECK_ERR_PATH), 		\
					$(SRC_CHECK_ERR_FILES:.c=.o))

OBJS_ENV_VAR	=	$(addprefix $(OBJ_ENV_VAR_PATH), 		\
					$(SRC_ENV_VAR_FILES:.c=.o))

OBJS_PARSING	=	$(addprefix $(OBJ_PARSING_PATH), 		\
					$(SRC_PARSING_FILES:.c=.o))

OBJS_EXECUTION	=	$(addprefix $(OBJ_EXECUTION_PATH), 		\
					$(SRC_EXECUTION_FILES:.c=.o))

OBJS_REDIR		=	$(addprefix $(OBJ_REDIR_PATH), 		\
					$(SRC_REDIR_FILES:.c=.o))

OBJS_SHELL		=	$(addprefix $(OBJ_SHELL_PATH), 		\
					$(SRC_SHELL_FILES:.c=.o))

OBJS	=	$(OBJS_BUILTINS)	$(OBJS_CHECK_ERR)	$(OBJS_ENV_VAR)	\
			$(OBJS_PARSING)		$(OBJS_EXECUTION)	$(OBJS_REDIR)	\
			$(OBJS_SHELL)


# ###################################### #
#               OBJ BUILD		         #
# ###################################### #

$(OBJ_BUILTINS_PATH)%.o: 	$(SRC_BUILTINS_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_CHECK_ERR_PATH)%.o: 	$(SRC_CHECK_ERR_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_ENV_VAR_PATH)%.o: 	$(SRC_ENV_VAR_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_PARSING_PATH)%.o: 	$(SRC_PARSING_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_EXECUTION_PATH)%.o: 	$(SRC_EXECUTION_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_REDIR_PATH)%.o: 		$(SRC_REDIR_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ_SHELL_PATH)%.o: 		$(SRC_SHELL_PATH)%.c $(MAKEFILE) $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $<


# ###################################### #
#                 RULES			         #
# ###################################### #

all: 		make_libft $(OBJS_DIRS) $(NAME)

make_libft:
			@$(MAKE) -C $(LIBFT_DIR)

$(LIBFT_A):	
			@$(MAKE) make_libft

$(OBJS_DIRS):
			mkdir -p $(OBJS_DIRS)

$(NAME): 	$(LIBFT_A) $(OBJS)
ifeq ($(UNAME),Linux)
	$(AR) $(ARFLAGS) $(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_A) $(RL_FLAGS)
	@echo "$(BGREEN)Linux Compilation Done$(NOCOLOR)"
else ifeq ($(UNAME),Darwin)
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_A) $(OBJS) $(RL_FLAGS)
	@echo "$(BGREEN)Mac OS Compilation Done$(NOCOLOR)"
endif

clean:
			@$(MAKE) clean -C $(LIBFT_DIR)
			$(RM) $(OBJS)
			@echo "$(BGREEN)Clean done$(NOCOLOR)"

fclean: 	
			@$(MAKE) fclean -C $(LIBFT_DIR)
			@$(MAKE) clean
			$(RM) $(NAME)
			$(RM) $(OBJS_DIRS)
			@echo "$(BGREEN)Fclean done$(NOCOLOR)"

re:			
			@$(MAKE) fclean
			@$(MAKE) all

.PHONY: 	all clean fclean re make_libft 
