# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkietwee <nkietwee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 16:21:02 by nkietwee          #+#    #+#              #
#    Updated: 2023/07/01 20:15:05 by nkietwee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

RM = rm -f

INC = minishell.h
LIBFT_PATH = Libft/
GET_NEXT_LINE_PATH = Get_next_line/
EXECUTE_PATH = Execute/
BUILTINS_PATH = Builtins/

# MINISHELL_SRCS = ft_minishell.c\

LIBFT_SRCS = ft_atoi.c\
            ft_isalnum.c\
			ft_isalpha.c\
            ft_isdigit.c\
            ft_putstr_fd.c\
            ft_split.c\
            ft_strchr.c\
            ft_strjoin.c\
            ft_strlen.c\
            ft_strncmp.c\
            ft_strnstr.c\
            ft_strtrim.c\

EXECUTE_SRCS = ft_execute.c \
                ft_init.c \
                ft_heredoc.c\

GET_NEXT_LINE_SRCS = get_next_line.c\
					get_next_line_utils.c\

BUILTINS_SRCS = ft_echo.c \
                ft_pwd.c \
                ft_cd.c \
                ft_prterr.c\
                ft_env.c \

SRCS = $(addprefix $(LIBFT_PATH), $(LIBFT_SRCS))\
	   $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS)) \
	$(addprefix $(EXECUTE_PATH), $(EXECUTE_SRCS))\
	$(addprefix $(BUILTINS_PATH), $(BUILTINS_SRCS))

# SRCS = $(EXECUTE_SRCS) \
#        $(addprefix $(LIBFT_PATH), $(LIBFT_SRCS)) \
#        $(addprefix $(GET_NEXT_LINE_PATH), $(GET_NEXT_LINE_SRCS))

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%o:%c $(INC)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -L/usr/local/lib -I/usr/local/include -lreadline $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
