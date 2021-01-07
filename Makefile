NAME = arx
SRC = arx.c \
base.c \
calc.c \
checker.c \
error.c \
extolst.c \
intvar.c \
operand.c \
plusminus.c \
postfix.c \
utils.c
OBJECTS = arx.o \
base.o \
calc.o \
checker.o \
error.o \
extolst.o \
intvar.o \
operand.o \
plusminus.o \
postfix.o \
utils.o
INC = ./
LIB = libft/libft.a

all: $(NAME)
	
$(NAME):
	@echo "Compiling library"
	@make -C ./libft
	@echo "Compiling arx"
	@gcc -g -Wextra -Werror -Wall -c $(SRC)
	@gcc -o $(NAME) -Wextra -Werror -Wall $(OBJECTS) $(LIB) -I $(INC)

clean:
	@echo "Removing libft object files"
	@make clean -C libft/
	@echo "Removing arx object files"
	@rm -f $(OBJECTS)

fclean: clean
	@echo "Removing libft library file"
	@make fclean -C libft/
	@echo "Removing arx executable file"
	@rm -f $(NAME)

re: fclean all
