CC = g++
CFLAGS = -Wall -std=c++11

# Исходные файлы
SRCS = main.cpp

# Имя исполняемого файла
EXEC = guess_number_game

# Имя динамической библиотеки
LIB = libprogram.so

all: $(EXEC)

$(EXEC): $(SRCS) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(SRCS) -L. -lprogram

.PHONY: clean

clean:
	rm -f $(EXEC)
