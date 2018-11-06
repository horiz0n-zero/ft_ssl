# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/27 14:29:24 by afeuerst          #+#    #+#              #
#    Updated: 2018/11/06 10:17:57 by afeuerst         ###   ########.fr        #
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

all: $(NAME)

$(NAME): $(SRC) $(INCLUDES)
	clang -I $(INCLUDES) $(SRC) $(FLAGS) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
