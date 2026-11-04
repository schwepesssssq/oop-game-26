CXX = g++
SRC_DIR = utilities
INC_DIR = utilities/headers
BUILD_DIR = build

CXXFLAGS = -std=c++20 -I$(INC_DIR) -Wall -Wextra -MMD
LIBS = -lpng -lm

TARGET = game

SRCS = $(wildcard $(SRC_DIR)/*.cpp) main.cpp
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS) -L/opt/homebrew/lib

$(BUILD_DIR)/main.o: main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean