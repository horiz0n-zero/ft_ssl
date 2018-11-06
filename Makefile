# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/27 14:29:24 by afeuerst          #+#    #+#              #
#    Updated: 2018/11/06 12:52:17 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
FLAGS = -fsanitize=address -O0 -g -Wall -Wextra -Werror
FLAGS += -Wno-unused-parameter -Wno-unused-const-variable
INCLUDES = ./includes/
SRC = ./sources/ft_ssl.c \
	./sources/ssl_get_algo.c \
	./sources/digest_verify_execute.c \
	./sources/cypher_base64_verify_execute.c \
	./sources/algo/algo_md5.c \
	./sources/algo/md5_body.c \
	./sources/algo/algo_sha256.c \
	./sources/algo/sha256_process.c \
	./sources/utility/ft_strcomparable.c \
	./sources/utility/ft_strlen.c \
	./sources/utility/ft_strcmp.c \
	./sources/utility/exits.c \
	./sources/utility/print_checksum.c \
	./sources/utility/error_strerror.c \
	./sources/utility/read_stdin.c \
	./sources/utility/ft_strndup.c \
	./sources/utility/ft_strjoin.c \
	./sources/utility/ft_memcpy.c
LIBPRINTF_DIRECTORY = ./libprintf/
LIBPRINTF = ./libprintf/libftprintf.a
LIBINCLUDES = ./libprintf/includes/

PRINT = printf "\33[38;5;39m%-27s -->> \33[38;5;220m%-27s\n"

all: $(NAME)

$(NAME): $(SRC) $(INCLUDES)
	@make -C $(LIBPRINTF_DIRECTORY)
	@echo $(SRC) | xargs -I @ -n 1 $(PRINT) "[ compiling ... ]" $(notdir @) &
	@clang -I $(LIBINCLUDES) -I $(INCLUDES) $(LIBPRINTF) $(SRC) $(FLAGS) -o $(NAME)
	@printf "\e[38;5;46m%s is now available !\n\e[0;37m" $(NAME)

clean:
	@make -C $(LIBPRINTF_DIRECTORY) clean

fclean: clean
	@make -C $(LIBPRINTF_DIRECTORY) fclean
	@rm -f $(NAME)
	@printf "\e[38;5;160m%s as been removed.\n\e[0;37m" $(NAME)

re: fclean all
