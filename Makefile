UP = "\033[A"
CLEAR = "\033[K"

MY_SOURCES =	srcs/main.c \
				srcs/parsing.c \
				srcs/tools.c \
				srcs/print.c \
				srcs/sorting.c \

MY_OBJECTS = $(MY_SOURCES:.c=.o)

INCLUDES = includes/

LIBFT = libft/libft.a

NAME = ft_ls

FLAGS = -g -Wall -Wextra -Werror -I $(INCLUDES)

all: $(NAME)

.c.o:
	@gcc $(FLAGS) -c $< -o $(<:.c=.o)
	@echo $(UP)"\033[0;93mCompiling ft_ls : $@ \033[0;39m                       "

$(NAME): $(LIB) $(MY_OBJECTS)
	@make -C libft/
	@gcc $(FLAGS) $(MY_OBJECTS) $(LIBFT) -o $(NAME)
	@echo "\033[0;92mFt_ls compiled\033[0;39m                                "
	@clear

clean:
	@rm -f $(MY_OBJECTS)
	@rm -f libft/*.o
	@echo "\033[0;92m.o files cleaned.\033[0;39m"

fclean: clean
	@rm -f $(NAME) $(NAME_LINUX)
	@rm -f libft/libft.a
	@echo "\033[0;92mFt_ls / Libft cleaned.\033[0;39m"

re: fclean all

.PHONY: all clean fclean re
