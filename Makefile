
# Compilation
NAME		=	lem_in
CC			=	clang
FLAGS		=	-Wall -Werror -Wextra -g3 -flto -march=native -Ofast
HEADER		=	-I$(PATH_INC)

# Color Code and template code
GREY = \033[2:49;39m
RED = \033[1;31m
GREEN = \033[3;32m
YELLOW = \033[3;49;33m
BLUE = \033[3;4;34m
BLUEE = \033[3;34m
PURPLE = \033[3;35m
CYAN = \033[3;36m
RESET = \033[0m
ICONOK = \033[1;32m
ICONKO = \033[1;31m
CO_DELET = \033[3;31m
CO_A_OUT = \033[96m
WHITE = \033[1;37m


# Path directories
PATH_INC	=	include
PATH_SRC	=	src
PATH_OBJ	=	obj

# Source
SRC			=	$(addprefix $(PATH_SRC)/, main.c \
				utils/ft_dlist.c \
				utils/ft_split.c \
				utils/function_lst_map.c \
				utils/function_lst_edge.c \
				utils/function_lst_vertex.c \
				utils/function_node.c \
				utils/get_next_line.c \
				utils/get_next_line_utils.c \
				utils/utils_memory.c \
				utils/utils_memory2.c \
				utils/utils_parsing.c \
				utils/utils_str.c \
				utils/utils_str2.c \
				parsing/process_lines.c \
				parsing/parsing.c \
				graph/data_to_graph.c \
				graph/utils_graph.c \
				graph/free_graph.c \
				)

OBJ			=	$(addprefix $(PATH_OBJ)/, $(SRC:.c=.o))

# Headers
INC_FILES	= lib.h

INC			=	$(addprefix $(PATH_INC)/, $(INC_FILES))

# Rules
all			:	$(NAME)

$(NAME)	:	$(OBJ) $(INC)
	@ $(CC) $(FLAGS) $(HEADER) $(OBJ) -o $(NAME)
	@ printf "\033[2K\r$(BLUE)$(NAME)$(RESET)$(BLUEE): $(ICONOK)Compiled [√]$(RESET)\n"

$(PATH_OBJ)/%.o		: 	%.c    $(INC)
	@ mkdir -p $(dir $@)
	@ printf "\033[2K\r$(PURPLE)$<: $(CYAN)loading..$(RESET)"
	@ $(CC) $(FLAGS) $(HEADER) -c  -o $@ $<

clean			:
				@ rm -rf ${obj}
				@ rm -rf obj

fclean	:	clean
	@ rm -rf $(NAME)
	@ printf "$(CYAN)'$(NAME)'$(RESET) and all .o has been $(RED)deleted. 🗑️\n$(RESET)"

re		:	fclean all

leaks	:
	@ make && leaks --atExit -- ./${NAME} < test.txt

run		:
	@ make && ./$(NAME) < test.txt

help	:
	@ printf "$(RESET)Welcom to Lem_in a project of algorithmic. \n$(RESET)"
	@ printf "$(RESET)\nCommand of the Makefile : \n\n$(RESET)"
	@ printf "$(RESET) - clean :        clean objs \n$(RESET)"
	@ printf "$(RESET) - fclean :       clean exec and objs\n$(RESET)"
	@ printf "$(RESET) - re :           clean and recompile\n$(RESET)"
	@ printf "$(RESET) - leaks :        recompile run and check leaks atExit\n$(RESET)"
	@ printf "$(RESET) - run :          recompile and run\n\n$(RESET)"

.PHONY: all compil clean fclean re leaks run help
