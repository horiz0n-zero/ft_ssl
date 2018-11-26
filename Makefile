# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/27 14:29:24 by afeuerst          #+#    #+#              #
#    Updated: 2018/11/24 13:23:09 by afeuerst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ssl
FLAGS = -fsanitize=address -O0 -g -Wall -Wextra -Werror
FLAGS += -Wno-unused-parameter
INCLUDES = ./includes/
SRC = ./sources/ft_ssl.c \
	./sources/ssl_get_algo.c \
	./sources/digest_verify_execute.c \
	./sources/cypher_base64_verify_execute.c \
	./sources/algo/algo_md5.c \
	./sources/algo/md5_body.c \
	./sources/algo/algo_sha256.c \
	./sources/algo/sha256_process.c \
	./sources/algo/algo_base64.c \
	./sources/algo/base64_decode.c \
	./sources/cypher_des_verify_execute.c \
	./sources/algo/algo_des.c \
	./sources/algo/des_process.c \
	./sources/algo/des_f.c \
	./sources/algo/des_block_ciphers.c \
	./sources/algo/des_padding.c \
	./sources/utility/ft_strcomparable.c \
	./sources/utility/ft_strlen.c \
	./sources/utility/ft_strcmp.c \
	./sources/utility/exits.c \
	./sources/utility/print_checksum.c \
	./sources/utility/read_source.c \
	./sources/utility/error_strerror.c \
	./sources/utility/read_stdin.c \
	./sources/utility/ft_strndup.c \
	./sources/utility/ft_strjoin.c \
	./sources/utility/ft_memcpy.c \
	./sources/utility/getpass.c \
	./sources/utility/args_to_value.c \
	./sources/utility/des_utility.c
SRC_FILE = $(notdir $(SRC))
LIBPRINTF_DIRECTORY = ./libprintf/
LIBPRINTF = ./libprintf/libftprintf.a
LIBINCLUDES = ./libprintf/includes/

PRINT = printf "\33[38;5;39m%-27s -->> \33[38;5;220m%-27s\n"

all: $(NAME)

$(NAME): $(SRC) $(INCLUDES)
	@make -C $(LIBPRINTF_DIRECTORY)
	@echo $(SRC_FILE) | xargs -I @ -n 1 $(PRINT) "source >" @ &
	@clang -I $(LIBINCLUDES) -I $(INCLUDES) $(LIBPRINTF) $(SRC) $(FLAGS) -o $(NAME)
	@printf "\e[38;5;46m%s is now available !\n\e[0;37m" $(NAME)

clean:
	@make -C $(LIBPRINTF_DIRECTORY) clean

fclean: clean
	@make -C $(LIBPRINTF_DIRECTORY) fclean
	@rm -f $(NAME)
	@printf "\e[38;5;160m%s as been removed.\n\e[0;37m" $(NAME)

re: fclean all
