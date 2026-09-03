# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ikawamuk <ikawamuk@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/30 03:18:23 by ikawamuk          #+#    #+#              #
#    Updated: 2026/09/03 09:23:40 by ikawamuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= libjson.a
TEST_NAME	:= rosetta_json

INC_DIR		:= include
SRC_DIR		:= src
OBJ_DIR		:= obj

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
LDLIBS 		:= -lm
CPPFLAGS	:= -I $(INC_DIR) -MMD -MP
AR			:= ar
ARFLAGS		:= rcs
RM			:= rm -f

# ---------------------------------------------------------------- sources -- #

SRCS		:= \
	$(SRC_DIR)/json_delete.c \
	$(SRC_DIR)/json_parse/json_parse.c \
	$(SRC_DIR)/json_parse/json_new_item.c \
	$(SRC_DIR)/json_parse/json_error.c \
	$(SRC_DIR)/json_parse/parse_buf.c \
	$(SRC_DIR)/json_parse/parse_null.c \
	$(SRC_DIR)/json_parse/parse_true.c \
	$(SRC_DIR)/json_parse/parse_false.c \
	$(SRC_DIR)/json_parse/parse_number.c \
	$(SRC_DIR)/json_parse/parse_string.c \
	$(SRC_DIR)/json_parse/json_array.c \
	$(SRC_DIR)/json_parse/parse_array.c \
	$(SRC_DIR)/json_parse/json_object.c \
	$(SRC_DIR)/json_parse/parse_object.c \
	$(SRC_DIR)/json_generate/json_generate.c \
	$(SRC_DIR)/json_generate/output_buf.c \
	$(SRC_DIR)/json_generate/json_generate.c \
	$(SRC_DIR)/json_generate/output_buf.c \
	$(SRC_DIR)/json_generate/generate_null.c \
	$(SRC_DIR)/json_generate/generate_true.c \
	$(SRC_DIR)/json_generate/generate_false.c \
	$(SRC_DIR)/json_generate/generate_number.c \
	$(SRC_DIR)/json_generate/generate_string.c \
	$(SRC_DIR)/json_generate/generate_string_ptr.c \
	$(SRC_DIR)/json_generate/generate_array.c \
	$(SRC_DIR)/json_generate/generate_object.c \
	$(SRC_DIR)/json_access/json_is_null.c \
	$(SRC_DIR)/json_access/json_is_true.c \
	$(SRC_DIR)/json_access/json_is_false.c \
	$(SRC_DIR)/json_access/json_is_number.c \
	$(SRC_DIR)/json_access/json_is_string.c \
	$(SRC_DIR)/json_access/json_is_array.c \
	$(SRC_DIR)/json_access/json_is_object.c \
	$(SRC_DIR)/json_access/json_get_number.c \
	$(SRC_DIR)/json_access/json_get_string.c \
	$(SRC_DIR)/json_access/json_get_array.c \
	$(SRC_DIR)/json_access/json_get_object.c \

TEST_SRCS := $(wildcard src/test/*.c)
TEST_OBJS := $(TEST_SRCS:src/test/%.c=obj/test_%.o)
TEST_TARGET := rosetta_json_test

OBJS		:= $(SRCS:%.c=$(OBJ_DIR)/%.o)
TEST_OBJS	:= $(TEST_SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS		:= $(OBJS:.o=.d) $(TEST_OBJS:.o=.d)

# ---------------------------------------------------------------- targets -- #

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# main.c をリンクした動作確認用の実行ファイル
$(TEST_NAME): $(TEST_OBJS) $(NAME)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(NAME) -o $@ $(LDLIBS)

test: $(TEST_NAME)

# デバッグビルド (シンボル + AddressSanitizer)
debug: CFLAGS += -g3 -fsanitize=address,undefined
debug: fclean $(TEST_NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME) $(TEST_NAME) $(TEST_TARGET)

re: fclean all

-include $(DEPS)

.PHONY: all test debug clean fclean re test
