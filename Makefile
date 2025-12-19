# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfontain <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 10:54:57 by mfontain          #+#    #+#              #
#    Updated: 2025/12/19 11:54:57 by mfontain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
SRCS	=	get_next_line.c get_next_line_utils.c

OBJS	= $(SRCS:.c=.o)
HEADERS = get_next_line.h

cc	= cc
RM	= rm -f
CFLAGS	= -Wall -Wextra -Werror -I.

NAME	= get_next_line.a

all:	$(NAME)

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)

$(OBJS):	$(HEADERS)

clean:		
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean $(NAME)

.PHONY:		all clean fclean re

