# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 18:51:59 by thmeyer           #+#    #+#              #
#    Updated: 2023/01/27 14:24:04 by thmeyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOCOLOR= \033[0m
BGREEN = \033[3;32m

NAME_C = client
NAME_S = server

CC = cc
C_FLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS_S = server.c
SRCS_C = client.c utils.c

OBJS_S = $(SRCS_S:%.c=$(DIR_OBJS_S)%.o)
OBJS_C = $(SRCS_C:%.c=$(DIR_OBJS_C)%.o)

DIR_OBJS_S = $(DIR_SRV)Objs/
DIR_OBJS_C = $(DIR_CLT)Objs/
DIR_PRINTF = ft_printf/
DIR_CLT = srcs_client/
DIR_SRV = srcs_server/

PRINTF_A = $(DIR_PRINTF)libftprintf.a

all: directory rsc $(NAME_S) $(NAME_C)

$(NAME_S): $(PRINTF_A) $(OBJS_S)
	$(CC) $(C_FLAGS) -o $(NAME_S) $(OBJS_S) $(PRINTF_A)

$(DIR_OBJS_S)%.o: $(DIR_SRV)%.c Makefile
	$(CC) $(C_FLAGS) -o $@ -c $< 

$(NAME_C): $(PRINTF_A) $(OBJS_C)
	$(CC) $(C_FLAGS) -o $(NAME_C) $(OBJS_C) $(PRINTF_A)
	
$(DIR_OBJS_C)%.o: $(DIR_CLT)%.c Makefile
	$(CC) $(C_FLAGS) -o $@ -c $< 

rsc:
	@$(MAKE) -C $(DIR_PRINTF)

clean:
	@$(MAKE) clean -C $(DIR_PRINTF)
	$(RM) $(DIR_OBJS_S)
	$(RM) $(DIR_OBJS_C)
	@echo "$(BGREEN)Clean done$(NOCOLOR)"
    
fclean: 
	@$(MAKE) fclean -C $(DIR_PRINTF)
	@$(MAKE) clean
	$(RM) $(NAME_S)
	$(RM) $(NAME_C)
	@echo "$(BGREEN)Fclean done$(NOCOLOR)"

re: 
	@$(MAKE) fclean
	@$(MAKE) all

directory:
	@mkdir -p $(DIR_OBJS_S)
	@mkdir -p $(DIR_OBJS_C)

.PHONY: all clean fclean re directory