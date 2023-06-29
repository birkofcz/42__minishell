# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 16:36:32 by sbenes            #+#    #+#              #
#    Updated: 2023/06/29 15:09:36 by sbenes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#color and formatting definitions:
BOLD =	\033[1m
GREEN =	\033[32m
RED =	\033[31m
BCYAN =	\033[96m
NC =	\033[0m

#name
NAME = 		minishell

# compiler
CC =		cc
CFLAGS =	-Wall -Wextra -Werror -g

#libft
LIBFT_PATH =	libft/
LIBFT_NAME =	libft.a
LIBFT =			$(LIBFT_PATH)$(LIBFT_NAME)

#Includes
INC =	-I ./include/\
		-I ./libft/

#sources
SRC_PATH =	src/
SRC = 	minishell.c prompt_crossroad.c builtin_echo.c \
		builtin_echo_utils.c builtins_cd_pwd.c builtin_env.c \
		builtin_export.c builtin_unset.c utils.c \
		parsing_quotes_env_vars.c executor_binary.c \
		heredoc.c tokenize_commands_args.c in_outfiles.c \
		command_check.c executor_builtin_forked.c executor_builtin_nonforked.c \
		args_lexer_parser.c signals.c
SRCS =	$(addprefix $(SRC_PATH), $(SRC))

#objects
OBJ_PATH =	obj/
OBJ =		$(SRC:.c=.o)
OBJS =		$(addprefix $(OBJ_PATH), $(OBJ))


all: $(LIBFT) $(NAME)

$(OBJ_PATH)%.o :$(SRC_PATH)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(OBJS): $(OBJ_PATH)

$(OBJ_PATH):
	@mkdir $(OBJ_PATH)

$(LIBFT):
	@echo "$(BOLD)$(GREEN)[ 🙉 Making libft... ]$(NC)"
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJS)
	@echo "$(BOLD)$(GREEN)[ 🙊 Compiling shit together... ]$(NC)"
	@$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS) $(LIBFT) $(INC)
	@echo "$(BOLD)$(GREEN)[ 🪄 Program ready! ]$(NC)"
	@echo ""
	@echo ""				
	@echo "$(BCYAN) __ _____ ____ __           _       _     _          _ _ "
	@echo "$(BCYAN)| _|_   _/ ___|_ |_ __ ___ (_)_ __ (_)___| |__   ___| | |"
	@echo "$(BCYAN)| |  | | \___ \| | '_   _ \| | '_ \| / __| '_ \ / _ \ | |"
	@echo "$(BCYAN)| |  | |  ___) | | | | | | | | | | | \__ \ | | |  __/ | |"
	@echo "$(BCYAN)| |  |_| |____/| |_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|"
	@echo "$(BCYAN)|__|          |__|                                       "
	@echo ""
	@echo "$(NC)"
	@echo "TS Team 2023"
	@echo "run ./minishell"
	@echo ""

bonus: all

clean:
	@echo "$(BOLD)$(RED)[ 🔥 Purging object files ]$(NC)"
	@rm -Rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@echo "$(BOLD)$(RED)[ 🔥 Removing program ]$(NC)"
	@rm -f $(NAME)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)

re: fclean all

.PHONY: all re clean fclean
