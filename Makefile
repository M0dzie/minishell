# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/23 18:51:59 by thmeyer           #+#    #+#              #
#    Updated: 2023/01/27 14:27:56 by thmeyer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NOCOLOR= \033[0m
BGREEN = \033[3;32m

NAME = 
HEADER = 

CC = cc
C_FLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRCS = main.c sl_utils.c check_errors.c back_tracking.c fill_map.c \
		init_mlx.c hooks.c

OBJS = $(SRCS:%.c=$(DIR_OBJS)%.o)

DIR_OBJS = Objs/
DIR_LIBFT = Libft/
DIR_MLX = Minilibx/

LIBFT_A = $(DIR_LIBFT)libft.a

all: directory rsc $(NAME)

$(NAME): $(LIBFTB_A) $(OBJS)
	$(CC) $(C_FLAGS) -o $(NAME) $(OBJS) $(LIBFT_A)

rsc:
	@$(MAKE) -C $(DIR_LIBFT)
	@$(MAKE) -C $(DIR_MLX)

$(DIR_OBJS)%.o: %.c Makefile $(HEADER)
	$(CC) $(C_FLAGS) -o $@ -c $< 

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

.PHONY: all clean fclean re directory