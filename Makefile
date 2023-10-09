# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 16:03:08 by roruiz-v          #+#    #+#              #
#    Updated: 2023/08/08 17:55:16 by roruiz-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	server

NAME2 = client

NAME_B = server_bonus

NAME2_B = client_bonus

#HDRS = minitalk.h

SRC	=	server.c

SRC2 = client.c		

SRC_B	=	server_bonus.c
				
SRC2_B = client_bonus.c		

OBJS = $(SRC:.c=.o)

OBJS2 = $(SRC2:.c=.o)

OBJS_B = $(SRC_B:.c=.o)

OBJS2_B = $(SRC2_B:.c=.o)

FLAGS	= -Wall -Werror -Wextra

LIBFT_PATH = libft/libft.a

all:	$(NAME) $(NAME2)

.c.o :
	gcc -c $(FLAGS) $< -o $@

$(NAME): $(LIBFT_PATH) $(OBJS)
	gcc $(FLAGS) $(OBJS) $(LIBFT_PATH) -o $(NAME)
	
$(NAME2): $(LIBFT_PATH) $(OBJS2)
	gcc $(FLAGS) $(OBJS2) $(LIBFT_PATH) -o $(NAME2)

$(NAME_B): $(LIBFT_PATH) $(OBJS_B)
	gcc $(FLAGS) $(OBJS_B) $(LIBFT_PATH) -o $(NAME_B)
 		
$(NAME2_B): $(LIBFT_PATH) $(OBJS2_B)
	gcc $(FLAGS) $(OBJS2_B) $(LIBFT_PATH) -o $(NAME2_B)

clean:
	rm -f $(OBJS) $(OBJS2) $(OBJS_B) $(OBJS2_B)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME2) $(NAME_B) $(NAME2_B)
	rm -f $(LIBFT_PATH)

re:	fclean all

bonus: $(NAME_B) $(NAME2_B) $(HDRS)

$(LIBFT_PATH):
	make -C libft all

.PHONY: all clean fclean re