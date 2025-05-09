# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tforster <tfforster@student.42sp.org.br    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 12:14:39 by tforster          #+#    #+#              #
#    Updated: 2025/04/16 16:34:32 by tforster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    Name                                                                      #
# **************************************************************************** #

BIN_DIR		:=	bin
TARGET		:=	$(BIN_DIR)/webserv

# **************************************************************************** #
#    Sources                                                                   #
# **************************************************************************** #

SRC_DIR		:=	src
SRC_FILES	:=	\
	main.c	\
	tcp.c	\
	http.c	\
	route.c	\
	filesystem.c

SRC_FILES	:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# **************************************************************************** #
#    Dependencies                                                              #
# **************************************************************************** #

INCLUDE_DIR	:=	include
LIB_DIR		:=	lib

# **************************************************************************** #
#    Build                                                                     #
# **************************************************************************** #

OBJ_DIR		:=	obj
OBJ_FILES	:=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

CC			:=	cc
CFLAGS		:=	-Wextra -Werror
INCLUDE		:=	$(addprefix -I , $(INC_DIR)) -MMD -MP
LIB			:=	$(addprefix -I , $(LIB_DIR)) -MMD -MP

DEBUG		:=	-O3
MSG			:=
SANITIZE	:=

# **************************************************************************** #
#    Misc                                                                      #
# **************************************************************************** #

RED			:= $(shell tput setaf 1)
GREEN		:= $(shell tput setaf 2)
YELLOW		:= $(shell tput setaf 3)
BLUE		:= $(shell tput setaf 4)
MAGENTA		:= $(shell tput setaf 5)
CYAN		:= $(shell tput setaf 6)
WHITE		:= $(shell tput setaf 7)
ERROR		:= $(shell tput setab 1)$(WHITE)
SUCCESS		:= $(shell tput setab 2)$(WHITE)
WARNING		:= $(shell tput setab 3)$(WHITE)
INFO		:= $(shell tput setab 4)$(WHITE)
BOLD		:= $(shell tput bold)
RESET		:= $(shell tput sgr0)
CLEAR		:= $(shell tput cuu1; tput el)
TITLE		:= $(YELLOW)$(basename $(TARGET))$(RESET)
TITLE_LOOSE	:= $(TITLE) $(MAGENTA)disable Werror$(RESET)
TITLE_MSG	:= $(TITLE) $(MAGENTA)with message$(RESET)
TITLE_DEBUG	:= $(TITLE) $(MAGENTA)debug$(RESET)
TITLE_ASAN	:= $(TITLE) $(MAGENTA)address sanitizer$(RESET)

# 1: action, 2: target, 3: color
define message
	$(info [$(TITLE)] $(3)$(1)$(RESET) $(2))
endef

# **************************************************************************** #
#    Targets                                                                   #
# **************************************************************************** #

all: $(TARGET) ## Build the program

$(TARGET): $(OBJ_FILES)
	mkdir -p $(dir $@)
	$(CC) $(SANITIZE) $(DEBUG) $(MSG) $(FLAGS) $^ -o $@
	$(call message,BINARY,$@,$(BLUE))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(SANITIZE) $(DEBUG) $(MSG) $(FLAGS) $(INCLUDE) $(LIB) -c $< -o $@
	$(call message,OBJECT,$@,$(GREEN))

loose:	## Build the program ignoring warnings
	$(MAKE) TITLE="$(TITLE_LOOSE)" FLAGS="$(filter-out -Werror,$(FLAGS))"

debug:	## Build the program with Debug symbols
	$(MAKE) fclean
	$(MAKE) TITLE="$(TITLE_DEBUG)" DEBUG=-"g3"

msg:	## Build the program with Constructor messages enabled
	$(MAKE) TITLE="$(TITLE_MSG)" MSG="-DMSG"

asan:	## Build the program with Debug and Address Sanitizer
	$(MAKE) TITLE="$(TITLE_ASAN)" SANITIZE="-fsanitize=address" DEBUG="-g3"

clean:	## Remove all generated object files
	rm -rf $(OBJ_DIR)
	$(call message,DELETED,$(OBJ_DIR),$(RED))

fclean:	## Remove all generated files
	$(MAKE) clean
	rm -rf $(TARGET)
	$(call message,DELETED,$(TARGET),$(RED))

re:		## Rebuild the program
	$(MAKE) fclean
	$(MAKE)

help:	## Show this message
	echo "$(BOLD)Usage: make [<name>=<value>...]$(RESET) $(BOLD)$(CYAN)[target...]$(RESET)"
	echo
	echo "$(BOLD)Targets:$(RESET)"
	grep -E '^[a-zA-Z_.%-]+:.*?## .*$$' Makefile \
	| awk 'BEGIN {FS = ":.*?## "}; {printf "%2s$(CYAN)%-20s$(RESET) %s\n", "", $$1, $$2}'

.PHONY: all loose debug msg asan clean fclean re help
.SILENT:
.DELETE_ON_ERROR:

-include $(DEP)
