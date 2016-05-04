# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpoujade <lpoujade@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/11 13:41:06 by lpoujade          #+#    #+#              #
#    Updated: 2016/05/04 16:19:00 by lpoujade         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
SRCDIR=./src
OBJDIR=./.obj

CC=gcc
CPPFLAGS=-Iincludes/ -Ilibft/includes -Imlx_src/
CFLAGS=-Wall -Werror -Wextra -g

LDFLAGS=-Llibft/ -Lmlx_src/
LDLIBS=-lft -lmlx
# GNU/Linux
# LDLIBS += -lXext -lX11
# Mac Os
 LDLIBS += -framework OpenGL -framework AppKit

# GCOV, llvm specific
# CFLAGS+=-g -fprofile-arcs -ftest-coverage
# LDFLAGS+=--coverage

LIB=libft/libft.a

SRC=fdf.c parse.c draw.c show_parse.c nd.c
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

covclean:
	-@rm $(OBJS:.o=.gcno) && echo "deleting" $(OBJS:.o=.gcno)
	-@rm $(OBJS:.o=.gcda) && echo "deleting" $(OBJS:.o=.gcda)

clean:
	-@rm $(OBJS) && echo "deleting" $(OBJS)

fclean: clean covclean
	-@rm $(NAME) && echo "deleting" $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

