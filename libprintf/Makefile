NAME = libftprintf.a

C_SRC = $(shell find ./srcs -type f | grep "\.c")
O_SRC = $(C_SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra
INCLUDES = -I ./includes

PRINT = printf "\e[38;5;39m%-27s -->> \e[38;5;46m%-27s\n"

all: $(NAME)

$(NAME): $(O_SRC)
	@ar -rsc $@ $^
	@printf "\e[38;5;190m%s is now available !\n\e[0;37m" $(NAME)

%.o: %.c
	@clang $< $(FLAGS) $(INCLUDES) -c -o $@ && $(PRINT) $(notdir $<) $(notdir $@)

clean:
	@rm -rf $(O_SRC)

fclean: clean
	@rm -rf $(NAME)
	@printf "\e[38;5;160m%s as been removed.\n\e[0;37m" $(NAME)

re: fclean all
