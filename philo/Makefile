# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpaterno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 18:20:36 by jpaterno          #+#    #+#              #
#    Updated: 2022/07/26 18:20:38 by jpaterno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

N_PHILO = philo

SRC =	main.c \
		m_thread.c \
		utils.c \
		actions.c \
	
OBJ = $(SRC:*.c=./.o)

all: $(N_PHILO)

$(N_PHILO): $(OBJ)
	gcc -c -pthread $(SRC)
	gcc -pthread -I /usr/local/include $(OBJ) -o $(N_PHILO)

clean:
	rm -f main.o m_thread.o utils.o actions.o

fclean: clean
	rm -f ./$(N_PHILO)
	rm -rf *.dSYM

save1:
	rm -rf /Users/jpaterno/Documents/SAVE1/*
	cp -rf * /Users/jpaterno/Documents/SAVE1/
save2:
	rm -rf /Users/jpaterno/Documents/SAVE2/*
	cp -rf * /Users/jpaterno/Documents/SAVE2/

fspace:
	rm -rf ~/Library/**.42_cache_bak*; rm -rf ~/**.42_cache_bak; brew cleanup

val:
	make re
	clear
	valgrind --tool=helgrind ./philo 5 410 200 200

re: fclean all