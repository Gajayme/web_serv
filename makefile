NAME = webserv

OBJS_DIR = obj

SRCS_DIR = src

SRCS = $(wildcard $(SRCS_DIR)/*.cpp)

HEADERS  = $(wildcard $(SRCS_DIR)/*.h)

OBJS = $(patsubst $(SRCS_DIR)/%.cpp, $(OBJS_DIR)/%.o, $(SRCS))

CXX = g++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

RM = rm -rf

RESET = "\033[0m"

BLACK = "\033[1m\033[37m"

all: $(NAME)

makeObjDir:
	@if [ ! -d $(OBJS_DIR) ]; then \
		mkdir $(OBJS_DIR); \
    fi


$(NAME) : $(OBJS) Makefile
	$(makeObjDir)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo $(BLACK)-webserv compiled $(RESET)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re makeObjDir

