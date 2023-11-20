CC = g++
CFLAGS = -Wall -std=c++11
LDFLAGS = -lm

# Исходные файлы
SRCS = program.cpp main.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Имя исполняемого файла
EXEC = guess_number_game

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(EXEC)
