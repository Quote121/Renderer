# CC = x86_64-w64-mingw32-g++.exe # 64 bit compiler

ifeq ($(OS),Windows_NT) # 32 bit compiler (Compatability)
	CC := i686-w64-mingw32-g++.exe
	FLAGS := -std=c++20 -Wall -g
else 
	CC := g++
	FLAGS := -std=c++20 -Wall -g
endif

# CXX_STANDARD := 20

SRC_DIR = src
RELEASE_DIR = release

TARGET := $(SRC_DIR)/textures

INCLUDE_PATHS =  -I"C:\msys64\mingw64\include" -I"include"
LIBRARY_PATHS =  -L"C:\msys64\mingw64\lib" -L"libs"

BUILD_PATH = "release"
OBJS_PATH = "releases/objs"

all: $(TARGET)

$(TARGET) : $(OBJS)
	$(CXX) $(LIB_DIRS) $(OBJS_PATH)/$(OBJS) $(LIBS) -o $(BUILD_PATH)/$(TARGET)

$(RELEASE_DIR)/objs/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(FLAGS) $(INCLUDE_PATHS) -c $< -o $(OBJS_PATH)/$@

clean:
