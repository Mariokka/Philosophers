# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mokatova <mokatova@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/07 18:14:55 by mokatova          #+#    #+#              #
#    Updated: 2022/04/24 18:23:52 by mokatova         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
HEADER = philo.h
CC = cc
FLAGS = -Wall -Werror -Wextra -pthread
RM = rm -f
SRC = main.c libft.c check_input.c deal_w_time.c init_structs.c \
			monitor.c start_threads.c stuff_to_do.c
OBJ = $(SRC:.c=.o)
%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@
all: $(NAME)
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all
.PHONY: all clean fclean re