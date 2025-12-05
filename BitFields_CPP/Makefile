# Makefile for BitFields C++ Project

CXX = g++
CXXFLAGS = -Wall -std=c++11
CC = gcc # Для лінкування С файлу

# Шляхи
SRC_DIR = src
TEST_DIR = tests
C_PROJECT_DIR = ../BitFields_C/src

# Цілі
TARGET = BitFieldsAppCPP
CROSS_TARGET = CrossTestApp

# Основний проект С++
SRCS = $(SRC_DIR)/BitFields.cpp $(TEST_DIR)/BitFields_test.cpp
OBJS = $(SRCS:.cpp=.o)

# Для крос-тесту нам потрібен об'єктний файл з С-проекту
CROSS_SRCS = $(TEST_DIR)/BitFields_cross_test.cpp $(SRC_DIR)/BitFields.cpp
C_OBJ = $(C_PROJECT_DIR)/BitFields.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Правило для запуску крос-тесту (потребує, щоб С-частина була скомпільована!)
cross:
	$(CXX) $(CXXFLAGS) -o $(CROSS_TARGET) $(CROSS_SRCS) $(C_OBJ)
	./$(CROSS_TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TEST_DIR)/*.o $(TARGET) $(CROSS_TARGET) TestResult_CPP.txt

run: $(TARGET)
	./$(TARGET)