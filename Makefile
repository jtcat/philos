NAME:= philo

CC:=cc

CFLAGS:= -Wall -Wextra -Werror

INC:= philo.h

SRC:=main.c utils.c

OBJ:=$(SRC:.c=.o)

%.o:	%.c $(INC)
	$(CC) -c $(CFLAGS) -o $@ $<

NAME:	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all:	$(NAME)

re:	fclean all

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)
