NAME = webserv

SRCS = $(wildcard src/*.cpp)

HEADERS  = $(wildcard src/*.h)

OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

obj/%.o: src/%.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++17
CXXFLAGS += -g3

RM = rm -rf

RESET = "\033[0m"
BLACK = "\033[1m\033[37m"

OBJS_DIR = "./obj"

all: $(NAME)
	@$(MAKE) $(NAME) -j5

makeObjDir:
	@if [ ! -d $(OBJS_DIR) ]; then \
		mkdir $(OBJS_DIR); \
    fi


$(NAME) : $(OBJS) $(HEADERS)
	$(makeObjDir)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo $(BLACK)-webserv compiled $(RESET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

