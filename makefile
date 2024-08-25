NAME = webserv

OBJS_DIR = obj
SRCS_DIR = src

# Поиск всех .cpp файлов в исходной директории
SRCS = $(shell find $(SRCS_DIR) -name '*.cpp')

# Генерация списка объектных файлов из исходных
OBJS = $(patsubst $(SRCS_DIR)/%.cpp,$(OBJS_DIR)/%.o,$(SRCS))

# Поиск всех заголовочных файлов в исходной директории
HEADERS = $(shell find $(SRCS_DIR) -name '*.h')

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -g3

# Правило для сборки объектных файлов
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Команды для удаления файлов
RM = rm -rf

# Цветовой вывод
RESET = "\033[0m"
BLACK = "\033[1m\033[37m"

# Основное правило
all: $(NAME)

# Правило для сборки исполняемого файла
$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo $(BLACK)-webserv compiled$(RESET)

# Правило для очистки объектных файлов
clean:
	$(RM) $(OBJS_DIR)

# Правило для полной очистки
fclean: clean
	$(RM) $(NAME)

# Правило для пересборки
re: fclean all

.PHONY: all clean fclean re
