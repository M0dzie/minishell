# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 18:51:59 by thmeyer           #+#    #+#              #
#    Updated: 2023/02/06 17:02:43 by thmeyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOCOLOR= \033[0m
BGREEN = \033[3;32m

NAME = minishell
HEADER = minishell.h

CC = cc
C_FLAGS = -Wall -Wextra -Werror
RL_FLAGS = -lreadline

RM = rm -rf

SRCS = main.c

OBJS = $(SRCS:%.c=$(DIR_OBJS)%.o)

DIR_OBJS = Objs/
DIR_LIBFT = Libft/

LIBFT_A = $(DIR_LIBFT)libft.a

all: directory rsc $(NAME)

$(NAME): $(LIBFT_A) $(OBJS)
	$(CC) $(C_FLAGS) $(RL_FLAGS) -o $(NAME) $(OBJS) $(LIBFT_A)

rsc:
	@$(MAKE) -C $(DIR_LIBFT)

$(DIR_OBJS)%.o: %.c Makefile $(HEADER)
	$(CC) $(C_FLAGS) $(RL_FLAGS) -o $@ -c $< 

clean:
	@$(MAKE) clean -C $(DIR_LIBFT)
	$(RM) $(OBJS)
	$(RM) $(DIR_OBJS)
	@echo "$(BGREEN)Clean done$(NOCOLOR)"
    
fclean: 
	@$(MAKE) fclean -C $(DIR_LIBFT)
	@$(MAKE) clean
	$(RM) $(NAME)
	@echo "$(BGREEN)Fclean done$(NOCOLOR)"

re: 
	@$(MAKE) fclean
	@$(MAKE) all

directory:
	@mkdir -p $(DIR_OBJS)

.PHONY: all clean fclean re rsc directory