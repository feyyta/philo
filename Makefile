# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcastrat <mcastrat.s19.be>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/30 14:45:25 by mcastrat          #+#    #+#              #
#    Updated: 2025/05/05 17:13:56 by mcastrat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[32m
CYAN = \033[36m
YELLOW = \033[33m
RESET = \033[0m
BLUE = \033[34m
RED = \033[31m
#valgrind ./philo 
#valgrind --tool=helgrind ./philo
CC = gcc
INCLUDES = -I./inc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

SRC_PATH = ./srcs
SRC = $(SRC_PATH)/main.c $(SRC_PATH)/utils.c $(SRC_PATH)/check.c $(SRC_PATH)/init.c $(SRC_PATH)/skills.c \
		$(SRC_PATH)/boss.c

OBJ_PATH = ./tmp
OBJ = $(OBJ_PATH)/main.o $(OBJ_PATH)/utils.o $(OBJ_PATH)/check.o $(OBJ_PATH)/init.o $(OBJ_PATH)/skills.o \
		$(OBJ_PATH)/boss.o
NAME = philo

all: $(NAME)

$(NAME): msg $(OBJ)
		@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
		@echo "\n$(GREEN)READY TO EAT SLEEP THINK.$(RESET)\n"

msg:
	@echo "\n$(BLUE)PHILOSOPHER 19$(RESET)\n"

clean: 
	   @echo "ciao $(YELLOW)philo$(RESET) obj..."
	   @rm -rf $(OBJ_PATH)
	   @echo "finish to clean$(YELLOW)philo$(RESET) obj!"

fclean: 
		@echo "\n$(GREEN)ca degage\n$(RESET)"
		@echo "$(YELLOW)ciao philo$(RESET) obj..."
	    @rm -rf $(OBJ_PATH)
	    @echo "$(YELLOW)finish to clean philo$(RESET) obj!"
		@rm -rf $(NAME)
		@echo "$(YELLOW)ciao exec$(RESET) file..."
		@echo "$(YELLOW)finish to clean exec$(RESET) file!"


re: fclean all

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
		@mkdir -p $(OBJ_PATH)
		@echo "$(RED)sous compilation...$<"
		@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re