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

SRC_DIR			:=	src
LOGGER_DIR		:=	$(SRC_DIR)/logger
PARSER_DIR		:=	$(SRC_DIR)/Parse
MODULE_DIR		:=	$(SRC_DIR)/module

SRC_FILES	:=	\
	main.cpp	\
	checkPath.cpp \
	Webserv.cpp

SRC_LOGGER	:= \
	Logger.cpp

SRC_PARSER	:= \
	CountingStream.cpp \
	Token.cpp \
	Parser.cpp \
	ParseException.cpp

SRC_MODULE	:= \
	Module.cpp \
	Core.cpp \
	CoreException.cpp \
	Http.cpp \
	Server.cpp \
	Location.cpp

SRC_FILES		:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
LOGGER_FILES	:= $(addprefix $(LOGGER_DIR)/, $(SRC_LOGGER))
PARSER_FILES	:= $(addprefix $(PARSER_DIR)/, $(SRC_PARSER))
MODULE_FILES	:= $(addprefix $(MODULE_DIR)/, $(SRC_MODULE))
ALL_FILES		:= \
	$(SRC_FILES) \
	$(LOGGER_FILES) \
	$(PARSER_FILES) \
	$(MODULE_FILES)

# **************************************************************************** #
#    Dependencies                                                              #
# **************************************************************************** #

INCLUDE_DIR	:=	include \
	include/logger \
	include/Parse \
	include/Module \
	include/Exception

LIB_DIR		:=	lib

# **************************************************************************** #
#    Build                                                                     #
# **************************************************************************** #

OBJ_DIR		:=	obj

OBJS_FILES	:= $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(ALL_FILES))
DEPS_FILES	:= $(patsubst %.cpp,$(OBJ_DIR)/%.d,$(ALL_FILES))

CC			:=	c++
# CFLAGS		:=	-Wall -Wextra -Werror -std=c++98
CFLAGS		:=	-std=c++98 -MMD -MP
INCLUDE		:=	$(addprefix -I, $(INCLUDE_DIR))
LIB			:=	$(addprefix -I, $(LIB_DIR))

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
#    Target                                                                    #
# **************************************************************************** #

all: $(TARGET) ## Build the program

$(TARGET): $(OBJS_FILES)
	mkdir -p $(dir $@)
	$(CC) $(SANITIZE) $(DEBUG) $(MSG) $(CFLAGS) $^ -o $@
	$(call message,BINARY,$@,$(BLUE))

# Unified rule: Compile .cpp → .o and generate .d
$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(SANITIZE) $(DEBUG) $(MSG) $(CFLAGS) $(INCLUDE) $(LIB) -c $< -o $@
	$(call message,OBJECT,$@,$(GREEN))

# **************************************************************************** #
#    Actions                                                                   #
# **************************************************************************** #

loose:	## Build the program ignoring warnings
	$(MAKE) TITLE="$(TITLE_LOOSE)" CFLAGS="$(filter-out -Werror,$(CFLAGS))"

debug:	## Build the program with Debug symbols
	$(MAKE) fclean
	$(MAKE) TITLE="$(TITLE_DEBUG)" DEBUG=-"g3"

msg:	## Build the program with Constructor messages enabled
	$(MAKE) TITLE="$(TITLE_MSG)" MSG="-DMSG"

asan:	## Build the program with Debug and Address Sanitizer
	$(MAKE) fclean
	$(MAKE) TITLE="$(TITLE_ASAN)" SANITIZE="-fsanitize=address" DEBUG="-g3"

clean:	## Remove all generated object files
	rm -rf $(OBJ_DIR)
	$(call message,DELETED,$(OBJ_DIR),$(RED))

fclean:	## Remove all generated files
	$(MAKE) clean
	rm -rf $(BIN_DIR)
	$(call message,DELETED,$(BIN_DIR),$(RED))

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

-include $(DEPS_FILES)


# Concept	| Meaning
# -c flag	| Compile only (no linking)
# $<		| First prerequisite (ex: the .cpp file)
# $@		| Target name (ex: .o or executable)
# $^		| All prerequisites (ex: all .o files)
# mkdir -p	| Create folders if they don't exist

# Part				| Means
# $(SRC_DIR)/%.cpp	| Match something like src/main.cpp, src/hello.cpp, etc.
# $(OBJ_DIR)/%.o	| Replace src/xxx.cpp with obj/xxx.o.
# $(SRC_FILES)		| List of your .cpp filenames (like main.cpp hello.cpp).

# pattern → needs %
# replacement → needs %
# text → your list


# Inside a Makefile
# test:
#	@echo $(patsubst src/%.cpp,obj/%.o,src/foo.cpp)
# Bash:
# make test
