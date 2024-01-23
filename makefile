NAME = webserv

SRCS = $(wildcard src/*.cpp)

HEADERS  = $(wildcard src/*.hpp)

OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

obj/%.o: src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXXFLAGS += -g3

RM = rm -rf

RESET = "\033[0m"
BLACK = "\033[1m\033[37m"

all:
	@$(MAKE) $(NAME) -j5

makeObjDir:
	rm -rf obj
	mkdir obj

$(NAME) : makeObjDir $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo $(BLACK)-webserv compiled $(RESET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

