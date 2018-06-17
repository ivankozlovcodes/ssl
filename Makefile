# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/08 21:31:12 by ikozlov           #+#    #+#              #
#    Updated: 2018/06/16 22:53:24 by ivankozlov       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl

# compiler
CC = gcc
DEBUG = -g
FLAGS = -Wall -Wextra -Werror
FLAGS += $(DEBUG)

# directories
OBJ_DIR = obj/
SRC_DIR = srcs/
INC_DIR = includes/
LIBFT_DIR = libft/

# md5
MD5_DIR = md5/
MD5_FILES = $(notdir $(wildcard $(MD5_DIR)*.c))
MD5 = $(addprefix $(MD5_DIR), $(MD5_FILES))
MD5_OBJFILES = $(MD5_FILES:%.c=%.o)
MD5_OBJ = $(addprefix $(OBJ_DIR)$(MD5_DIR), $(MD5_OBJFILES))

# files
SRC_FILES = $(notdir $(wildcard $(SRC_DIR)*.c))
OBJ_FILES = $(SRC_FILES:%.c=%.o)

# full paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
OBJ += $(MD5_OBJ)

# libraries
LIBFT = $(LIBFT_DIR)libft.a
LIB = $(LIBFT)

# includes
INCLUDES = -I $(LIBFT_DIR)includes -I $(INC_DIR)

all: $(NAME)

$(LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) $(LIB)
	@echo "[INFO] $(NAME) executable created"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)md5/%.o: $(MD5_DIR)%.c $(LIB)
	@mkdir -p $(OBJ_DIR)$(MD5_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d "./$(OBJ_DIR)" ]; then\
		/bin/rm -rf $(OBJ_DIR);\
		/bin/echo "[INFO] Objects removed.";\
	fi;

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@if test -e $(NAME); then\
		/bin/rm $(NAME);\
		/bin/echo "[INFO] $(NAME) executable deleted";\
	fi;

re: fclean all

.PHONY: all $(NAME) clean fclean re norm