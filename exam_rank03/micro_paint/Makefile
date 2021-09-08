# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/08 14:17:43 by ysoroko           #+#    #+#              #
#    Updated: 2021/09/08 16:33:58 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UTILS	=	utils/ft_string_utils.c \
			utils/ft_print_utils.c \

SRC		=	$(UTILS) \
			ft_main.c \

OBJS	=	$(SRC:.c=.o)

EXEC	=	micro_paint

ARG		=	test

all: $(OBJS)
	gcc $(OBJS) -I include -o $(EXEC) && ./$(EXEC) $(ARG)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(EXEC)

re: fclean all