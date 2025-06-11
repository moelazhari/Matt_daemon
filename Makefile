RED=\033[0;31m
GREEN=\033[0;32m
PURPLE=\033[0;35m

NAME = Matt_daemon
CC = g++
FLAGS = -Wall -Wextra -Werror

INCLUDES = includes

SRC_DIR = src
B_DIR = build

FILES = main Daemon Server TintinReporter
SRCS = $(addprefix $(SRC_DIR)/, $(FILES:=.cpp))
OBJS = $(addprefix $(B_DIR)/, $(FILES:=.o))

all: $(NAME)

$(B_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -I$(INCLUDES) -c $< -o $@
	@echo "$(GREEN)Compiling $<"

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lpthread
	@echo "$(PURPLE)Built $(NAME) successfully."

clean:
	@rm -f $(OBJS)
	@rm -rf $(B_DIR)
	@echo "$(RED)Cleaning build files..."

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Full clean done."

re: fclean all

.PHONY: all clean fclean re
