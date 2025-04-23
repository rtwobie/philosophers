# config
NAME	:= philo
CC		:= cc
SRC_DIR	:= src/
INC_DIR	:= inc/
OBJ_DIR	:= obj/

CFLAGS	:=
CFLAGS	+= -O2
CFLAGS	+= -Wall
CFLAGS	+= -Wextra
CFLAGS	+= -Werror
CFLAGS	+= -pedantic
CFLAGS	+= -Wconversion
CFLAGS	+= $(ADDFLAGS)

CPPFLAGS	:=
CPPFLAGS	+= -I$(INC_DIR)

LDFLAGS	:=

LDLIBS	:=

ifeq ($(DEBUG), 1)
	CFLAGS	+= -ggdb3 -O0
	LDFLAGS	+= -ggdb3 -O0
endif

# sources
SRC		:=

vpath %.c src/
SRC		+= main.c

OBJ		:= $(SRC:.c=.o)
OBJ		:= $(addprefix $(OBJ_DIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re:
	@make fclean
	@make all

valtest:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$(NAME) $(ARGS)

.PHONY: all clean fclean re
.PHONY: valtest
