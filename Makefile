# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/04/19 16:32:31 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
SRCDIR=./src
OBJDIR=./.obj

CC=clang
CPPFLAGS=-Iincludes/ -Ilibft/includes -Imlx_src/
CFLAGS=-Wall -Werror -Wextra -g

LDFLAGS=-Llibft/ -Lmlx_src/
LDLIBS=-lft -lmlx -lXext -lX11 #-framework OpenGL -framework AppKit

LIB=libft/libft.a

SRC=fdf.c parse.c draw.c show_parse.c
OBJ=$(SRC:.c=.o)

SRCS=$(addprefix $(SRCDIR)/,$(SRC))
OBJS=$(addprefix $(OBJDIR)/,$(OBJ))

all: $(LIB) $(NAME)

$(NAME): $(OBJS)
	@$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS) && echo "linking to\033[32m" $@ "\033[0m"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ && echo "compiling\033[36m" $@ "\033[0m"

$(LIB):
	make -C libft/

clean:
	-@rm $(OBJS) && echo "deleting" $(OBJS)

fclean: clean
	-@rm $(NAME) && echo "deleting" $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

