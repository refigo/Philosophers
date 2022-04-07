# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/23 17:02:05 by mgo               #+#    #+#              #
#    Updated: 2022/03/30 16:02:30 by mgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[0;33m"
WHITE		=	"\033[0;37m"
BRED		=	"\033[1;31m"
BGREEN		=	"\033[1;32m"
BYELLOW		=	"\033[1;33m"
BWHITE		=	"\033[1;37m"
ENDCOLOR	=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

NAME		=	philo_bonus

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		+=	-fsanitize=address -g
RM			=	rm -rf

INC_PATH	=	./inc/
SRC_PATH	=	./src/
DIR_UTIL	=	utils/
OBJ_PATH	=	./obj/

SRC_LIST	=	main_bonus.c \
				set_data_bonus.c \
				have_dining_bonus.c \
				process_philo_bonus.c \
				monitor_routine_bonus.c \
				$(DIR_UTIL)are_args_only_nums_bonus.c \
				$(DIR_UTIL)mgo_atoi_bonus.c \
				$(DIR_UTIL)mgo_calloc_bonus.c \
				$(DIR_UTIL)mgo_putstr_fd_bonus.c \
				$(DIR_UTIL)mgo_strlen_bonus.c \
				$(DIR_UTIL)error_with_msg_bonus.c \
				$(DIR_UTIL)set_time_ms_bonus.c \
				$(DIR_UTIL)sleep_shortly_ms_bonus.c \
				$(DIR_UTIL)print_philos_bonus.c \
				test_philo_bonus.c # to remove
SRC			=	$(addprefix $(SRC_PATH), $(SRC_LIST))

OBJ_LIST	=	$(SRC_LIST:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_LIST))

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
	@echo $(YELLOW) "Compling...\t" $< $(ENDCOLOR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)$(DIR_UTIL) 2> /dev/null || true
	@$(CC) $(CFLAGS) -I $(INC_PATH) -c $< -o $@

$(NAME)	:	$(OBJ)
	@echo $(GREEN) "Source files are compiled!\n" $(ENDCOLOR)
	@echo $(YELLOW) "Building $(NAME)..."
	@$(CC) $(CFLAGS) -I $(INC_PATH) $(OBJ) -o $(NAME)
	@echo $(GREEN) "$(NAME) is created!\n" $(ENDCOLOR)

all		:	$(NAME)

bonus	:	$(NAME)

clean	:
	@echo $(YELLOW) "Cleaning object files..." $(ENDCOLOR)
	@$(RM) $(OBJ_PATH)
	@echo $(RED) "Object files are cleaned!\n" $(ENDCOLOR)

fclean	: clean
	@echo $(YELLOW) "Removing $(NAME)..." $(ENDCOLOR)
	@$(RM) $(NAME)
	@echo $(RED) "$(NAME) is removed!\n" $(ENDCOLOR)

re	:	fclean all

.PHONY	:	all bonus clean fclean re
