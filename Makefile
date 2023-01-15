# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfergani <kfergani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 19:30:32 by kfergani          #+#    #+#              #
#    Updated: 2022/12/06 01:31:09 by kfergani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= philo
HEADERS		= ./include
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -pthread -g
SRC_DIR		= src/
SRCS		= $(addprefix $(SRC_DIR), main.c philo.c routine.c init.c utils.c)
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I $(HEADERS) $(SRCS) -o $(NAME)

$(OBJS): %.o:%.c
	@$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re