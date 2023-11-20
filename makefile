CC = g++
CFLAGS = -Wall -std=c++11

# Исходные файлы
SRCS = main.cpp

# Имя исполняемого файла
EXEC = program

# Имя динамической библиотеки
LIB = libprogram.so

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) -ldl

.PHONY: clean

clean:
	rm -f $(EXEC)

