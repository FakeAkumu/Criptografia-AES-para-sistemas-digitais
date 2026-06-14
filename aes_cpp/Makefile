CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -std=c++20 -g

BIN_DIR = bin
SRC_DIR = src
TEST_DIR = tests

TARGET = $(BIN_DIR)/aes
TEST_TARGET = $(BIN_DIR)/test_aes

SRCS = main.cpp $(SRC_DIR)/aes.cpp
OBJS = $(SRCS:.cpp=.o)

TEST_SRCS = $(TEST_DIR)/test_aes.cpp $(SRC_DIR)/aes.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET)

$(TEST_TARGET): $(TEST_OBJS) | $(BIN_DIR)
	$(CXX) $(TEST_OBJS) -o $(TEST_TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	rm -rf $(BIN_DIR)

.PHONY: all run test clean
