NAME = arx
SRC = arx.c \
base.c \
calc.c \
checker.c \
checker_op.c \
extolst.c \
intvar.c \
plusminus.c \
postfix.c \
utils.c
OBJECTS = arx.o \
base.o \
calc.o \
checker.o \
checker_op.o \
extolst.o \
intvar.o \
plusminus.o \
postfix.o \
utils.o
INC = ./
LIB = libft/libft.a

all: $(NAME)
	
$(NAME):
	make -C ./libft
	gcc -Wextra -Werror -Wall -c $(SRC)
	gcc -o $(NAME) -Wextra -Werror -Wall $(OBJECTS) $(LIB) -I $(INC)

clean:
	make clean -C libft/
	rm -f $(OBJECTS)

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean all
