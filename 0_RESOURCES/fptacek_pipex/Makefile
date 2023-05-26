# env
PROGRAM = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

# header
HEADER = pipex.h

# main
SRC_M = pipex.c utils.c
OBJ_M = $(SRC_M:.c=.o)

# libft
SRC_LIBFT = ft_split.c \
			ft_strdup.c \
			ft_strncmp.c \
		#	ft_substr.c \
			ft_strjoin.c \
			ft_strlen.c 
OBJ_LIBFT = $(SRC_LIBFT:.c=.o)

# get_next_line
SRC_GNL = gnl/get_next_line_utils.c \
			gnl/get_next_line.c \
			gnl/ft_substr.c
OBJ_GNL = $(SRC_GNL:.c=.o)

# make
%.o: %.c 		$(HEADER) Makefile
						@$(CC) $(FLAGS) -c $< -o $@

(PROGRAM):		$(OBJ_M) $(OBJ_LIBFT) $(OBJ_GNL)
						@echo "Compiling..."
						@$(CC) $(OBJ_M) $(OBJ_LIBFT) $(OBJ_GNL) -o $(PROGRAM)
						@echo "$(PROGRAM) created!"

all: $(PROGRAM)

clean:
						@$(RM) $(OBJ_M)
						@$(RM) $(OBJ_LIBFT)
						@$(RM) $(OBJ_GNL)
						@echo "Object files deleted!"

fclean:			clean
						@$(RM) $(PROGRAM)
						@echo "All deleted!"

re:				fclean all
