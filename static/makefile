CC = g++
CFLAGS = -Wall -std=c++11

# Исходные файлы
SRCS = program.cpp main.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Имя статической библиотеки
LIB = libprogram.a

# Имя исполняемого файла
EXEC = guess_number_game

all: $(LIB) $(EXEC)

$(LIB): $(OBJS)
	ar rcs $@ $^

$(EXEC): $(LIB)
	$(CC) $(CFLAGS) -o $@ main.o -L. -lprogram

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC) $(LIB)

