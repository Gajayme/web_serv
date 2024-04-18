NAME = webserv

SRCS = $(wildcard src/*.cpp)

HEADERS  = $(wildcard src/*.h)

OBJS = $(patsubst src/%.cpp, obj/%.o, $(SRCS))

obj/%.o: src/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

CXXFLAGS = -std=c++11 -g3
// CXXFLAGS += -Werror -Wall -Wextra

RM = rm -rf

RESET = "\033[0m"
BLACK = "\033[1m\033[37m"

OBJS_DIR = "./obj"

all: $(NAME)

makeObjDir:
	@if [ ! -d $(OBJS_DIR) ]; then \
		mkdir $(OBJS_DIR); \
    fi

$(NAME) : makeObjDir $(OBJS) 
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo $(BLACK)-webserv compiled $(RESET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re makeObjDir

