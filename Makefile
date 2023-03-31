# By default the 32 bit version will be compiled unless specifed in build commands
# 


# ifeq ($(OS),Windows_NT) # 32 bit compiler (Compatability)
# 	CC = i686-w64-mingw32-g++.exe
# 	CXX =
# 	CFLAGS = -m32
# 	CXXFLAGS = -std=c++20 -Wall -Wextra -g
# else # unix
# 	CC = gcc
# 	CXX = g++
# 	CFLAGS = -m32 -Wall -Wextra
# 	CXXFLAGS = -std=c++20 -Wall -g -w32
# endif

CFLAGS = -m32 -Wall -Wextra
CXXFLAGS = -std=c++20 -Wall -Wextra

# For 64-bit version
# make MODE=64
ifeq ($(MODE), 64)
	GLFWVER = GLFW_64
	CC = gcc
	CXX = g++
	CFLAGS := $(filter-out -m32, $(CXXFLAGS))
	CXXFLAGS := $(filter-out -m32, $(CXXFLAGS))
## Building for 32 bit
else
	GLFWVER = GLFW_32
	CC = gcc
	ifeq ($(OS),Windows_NT)
		CXX = i686-w64-mingw32-g++.exe
	else
		CXX = g++
	endif
endif

# For debugging
# make DEBUG=1
ifdef DEBUG
	CXXFLAGS += -g
	CFLAGS += -g
endif

PROGRAM = textures.exe
SRCDIR = src
BUILDDIR = release
TARGET = $(CURDIR)/$(BUILDDIR)/$(PROGRAM)

$(info Target : $(TARGET))
C_SOURCES = $(wildcard $(SRCDIR)/*.c)
$(info $(C_SOURCES) found!)
C_OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(C_SOURCES))

CPP_SOURCES = $(wildcard $(SRCDIR)/*.cpp)
$(info $(CPP_SOURCES) found!)
CPP_OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(CPP_SOURCES))


# Static library for glfw
LIBFLAGS = -lopengl32
LIBFLAGS += $(CURDIR)/libs/$(GLFWVER)/libglfw3.a
LIBFLAGS += -lgdi32

# Library DIR and Include DIR
INCLUDEPATHS = -I$(CURDIR)/include
LIBRARYPATHS = -L$(CURDIR)/libs/$(GLFWVER)


# ifeq ($(MODE), 64)
# 	$(info ===========32-bit============)
# else
# 	$(info ===========64-bit============)
# endif
$(info =============================)
$(info CFLAGS : $(CFLAGS))
$(info CXXFLAGS : $(CXXFLAGS))
$(info CC : $(CC))
$(info CXX : $(CXX))
$(info LIBFLAGS : $(LIBFLAGS))
$(info GLDWVER : $(GLFWVER))
$(info INCLUDEPATHS : $(INCLUDEPATHS))
$(info LIBRARYPATHS : $(LIBRARYPATHS))
$(info =============================)

all: $(TARGET)

# $^ is prerequisits (c objs and cpp objs)
# $@ is target
$(TARGET) : $(C_OBJECTS) $(CPP_OBJECTS)
	$(CXX) $^ -o $@ $(LIBFLAGS)

# $< evaluates to the first prerequisite
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDEPATHS) -c $< -o $@ 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(FLAGS) $(INCLUDEPATHS) $(LIBRARYPATHS) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
