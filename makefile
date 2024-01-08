NAME = webserv

SRCS = 0

HEADERS  = 0

OBJS = $(SRCS:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
CXXFLAGS += -g3

RM = rm -rf

RESET = "\033[0m"
BLACK = "\033[1m\033[37m"

all:
  @$(MAKE) $(NAME) -j5
$(NAME) : $(OBJS) $(HEADERS)
  $(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
  @echo $(BLACK)-webserv compiled $(RESET)

clean:
  $(RM) $(OBJS)

fclean: clean
  $(RM) $(NAME)

re:   fclean all

.PHONY: all clean fclean re

