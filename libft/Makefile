# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bluff <bluff@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/19 19:26:33 by bluff             #+#    #+#              #
#    Updated: 2018/01/23 11:48:13 by fle-roy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
PRINTF_DIR = ft_printf
GNL_DIR = gnl

SRCS_GNL = $(addprefix $(GNL_DIR)/, get_next_line.c)

SRCS_LIBFT = $(addprefix $(LIBFT_DIR)/, ft_any.c ft_atoi.c ft_bzero.c \
ft_count_if.c ft_factorial.c ft_find_next_prime.c ft_foreach.c ft_isalnum.c \
ft_isalpha.c ft_isascii.c ft_isdigit.c ft_islowercase.c ft_isprime.c \
ft_isprint.c ft_issort.c ft_isuppercase.c ft_itoa.c ft_lstat.c \
ft_lstfind.c ft_lstforeach.c ft_lstforeach_if.c ft_lstlast.c \
ft_lstmerge.c ft_lstpush_back.c ft_lstpush_front.c ft_lstremove_if.c \
ft_lstreverse.c ft_lstsize.c ft_lstsort.c ft_lstadd.c ft_lstdel.c \
ft_lstdelone.c ft_lstiter.c ft_lstmap.c ft_lstnew.c ft_map.c ft_memalloc.c \
ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
ft_memset.c ft_pow.c ft_putchar.c ft_putchar_fd.c \
ft_putendl.c ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c \
ft_putstr_fd.c ft_range.c ft_sqrt.c ft_strcat.c ft_strchr.c ft_strclr.c \
ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c \
ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c \
ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c \
ft_strrchr.c ft_strrev.c ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c \
ft_swap.c ft_tolower.c ft_toupper.c ft_atoi_base.c ft_iswhitespace.c \
ft_btree_apply_infix.c ft_btree_apply_suffix.c ft_btree_apply_prefix.c \
ft_btree_create_node.c ft_btree_insert_data.c ft_perror.c ft_btree_destroy.c \
ft_btree_count_node.c ft_itoa_base.c ft_numlen.c ft_getenv.c ft_free2d.c \
ft_str2ddup.c ft_haschar.c ft_free.c ft_strsplit_multi.c ft_lstdestroy.c)

SRCS_PRINTF = $(addprefix $(PRINTF_DIR)/, ft_printf.c ft_printf_utils.c \
		ft_printf_string.c ft_printf_parser.c \
		ft_printf_parameters.c ft_printf_utils2.c ft_printf_numbers.c \
		ft_printf_utils3.c ft_printf_numbers_upper.c ft_printf_wstring.c \
		ft_printf_utils4.c ft_printf_extract_dynamic_param.c \
		ft_printf_numbers2.c)

INCLUDES = include
CFLAGS =-c -Wall -Wextra -Werror -I $(INCLUDES)
OBJS = objs
CC = cc
LN = ar
LFLAGS = rsc
BIN = bin
OBJS_GNL = $(SRCS_GNL:$(GNL_DIR)/%.c=$(OBJS)/%.o)
OBJS_PRINTF = $(SRCS_PRINTF:$(PRINTF_DIR)/%.c=$(OBJS)/%.o)
OBJS_LIBFT = $(SRCS_LIBFT:$(LIBFT_DIR)/%.c=$(OBJS)/%.o)
NAME = $(addprefix ./$(BIN)/, libft.a)
all: $(NAME)
test:
	echo $(NAME)
$(OBJS)/%.o: $(LIBFT_DIR)/%.c
	@printf "\r\033[K[LIBFT] \033[1;32mBuilding $<\033[0m"
	@$(CC) $(CFLAGS) $< -o $@
$(OBJS)/%.o: $(PRINTF_DIR)/%.c
	@printf "\r\033[K[PRINTF] \033[1;32mBuilding $<\033[0m"
	@$(CC) $(CFLAGS) $< -o $@
$(OBJS)/%.o: $(GNL_DIR)/%.c
	@printf "\r\033[K[GNL] \033[1;32mBuilding $<\033[0m"
	@$(CC) $(CFLAGS) $< -o $@
$(NAME): $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_GNL)
	@printf "\r\033[K[LIBFT_TOTAL] \033[1;32mLinking...\033[0m\n"
	@$(LN) $(LFLAGS) $(NAME) $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_GNL)
	@printf "\n[LIBFT_TOTAL] \033[1;32mDone!\033[0m\n"
clean:
	@rm -f $(OBJS_LIBFT) $(OBJS_PRINTF) $(OBJS_GNL)
	@printf "[LIBFT_TOTAL] \033[1;31mCleaned .o!\033[0m\n"

fclean: clean
	@rm -f $(NAME)
	@printf "[LIBFT_TOTAL] \033[1;31mCleaned .a!\033[0m\n"
re:
	@$(MAKE) fclean
	@$(MAKE) all
.PHONY: all clean fclean re libft gnl printf
