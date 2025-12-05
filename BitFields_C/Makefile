# Makefile for BitFields C Project

CC = gcc
CFLAGS = -Wall -std=c99
TARGET = BitFieldsApp

# Директорії
SRC_DIR = src
TEST_DIR = tests

# Файли
SRCS = $(SRC_DIR)/BitFields.c $(TEST_DIR)/BitFields_test.c
OBJS = $(SRCS:.c=.o)

# Головна ціль
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Правило для компіляції .c в .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Очистка
clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET) TestResult.txt

# Запуск
run: $(TARGET)
	./$(TARGET)