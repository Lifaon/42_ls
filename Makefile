# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlantonn <mlantonn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/21 22:00:00 by mlantonn          #+#    #+#              #
#    Updated: 2019/04/10 14:28:01 by mlantonn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GRE = \033[32m
YEL = \033[33m
BLU = \033[34m
MAG = \033[35m
CYA = \033[36m
EOC = \033[39m

NAME = ft_ls
DIR_NAME = ft_ls

DIR_FT_PRINTF = ft_printf

CFLAGS = #-Wall -Wextra -Werror

INCS = $(INC) $(INC_FT_PRINTF)
INC = -I includes
INC_FT_PRINTF = -I $(DIR_FT_PRINTF)/includes

LIBS = $(LIB_FT_PRINTF)
LIB_FT_PRINTF = -L $(DIR_FT_PRINTF) -lftprintf

OBJS = $(SRCS:.c=.o)
OBJS_DIR = ./objs
OBJS_SUB_DIRS = 
OBJS_PRE = $(addprefix $(OBJS_DIR)/, $(OBJS))

SRCS_DIR = srcs
SRCS =	main.c \
		ft_readdir.c \
		get_data.c \
		print_contents.c \
		utils.c

.PHONY = all $(OBJS_DIR) $(NAME) clean fclean re

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "gcc $(CFLAGS) $(INCS) -c $^ -o $(CYA)$@$(EOC)"
	@gcc $(CFLAGS) $(INCS) -c $^ -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@if [ "$(OBJS_SUB_DIRS)" != "" ]; then \
		mkdir -p $(addprefix $(OBJS_DIR)/, $(OBJS_SUB_DIRS)); \
	fi

$(NAME): $(OBJS_DIR) $(OBJS_PRE)
	@make -C $(DIR_FT_PRINTF)
	@echo "gcc $(CFLAGS) $(OBJS_PRE) $(LIBS) -o $(MAG)$(NAME)$(EOC)"
	@gcc $(CFLAGS) $(OBJS_PRE) $(LIBS) -o $(NAME)

clean:
	@make clean -C $(DIR_FT_PRINTF)
	@echo "$(RED)rm -rf$(EOC) $(OBJS_DIR) from $(DIR_NAME)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@make fclean -C $(DIR_FT_PRINTF)
	@echo "$(RED)rm -rf$(EOC) $(NAME)"
	@rm -rf $(NAME)

re: fclean all

# debug rules

debug: change_cflag all

re_debug: fclean debug

change_cflag:
	@$(eval CFLAGS = -fsanitize=address)
