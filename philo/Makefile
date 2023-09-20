NAME:= philo

CC:=cc

CFLAGS:= -g -pthread -Wall -Wextra -Werror

INC:= philo.h

SRC:= main.c philo_actions.c utils.c utils2.c

OBJ:= $(SRC:.c=.o)

%.o:	%.c $(INC)
	$(CC) -c $(CFLAGS) -o $@ $<

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all:	$(NAME)

re:	fclean all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)
