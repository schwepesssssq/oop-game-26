CXX = g++
CXXFLAGS = -std=c++20 -Iutilities/headers -I. -Wall -Wextra -MMD
LIBS = -lpng -lm -L/opt/homebrew/lib
BUILD_DIR = build
TARGET = game

# Собираем все .cpp файлы: из корня, из utilities и из abilities
SRCS = main.cpp \
       Inventory.cpp \
       $(wildcard utilities/*.cpp) \
       $(wildcard abilities/*.cpp)

# Преобразуем пути (например, utilities/Map.cpp) в имена объектных файлов (build/Map.o)
OBJS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(notdir $(SRCS)))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

# Правило для сборки объектных файлов из ЛЮБОЙ директории
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Указываем, откуда брать файлы, если они не в корне (нужно для поиска .cpp)
vpath %.cpp utilities abilities .

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean