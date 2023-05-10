# For debug mode use DEBUG=1 in the same way as MODE
# 
# clean to clean release folder of .o and exe
#
# Here by default the code compiles with static libraries. Dynamic library compilation is not done yet
#
# TODO : dynamic library compiation

# For MINGW
# Check if the environment variables are set in a way that 64 bit comes before 32 bit as compiling in 32 will cause linking error
# this is for WINDOWS_NT
# 

CFLAGS = -Wall -Wextra
CXXFLAGS = -std=c++20 -Wall -Wextra

CC = gcc
CXX = g++

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
ifeq ($(OS),Windows_NT)
	# Static library for glfw
	LIBFLAGS = -lopengl32 -lgdi32
	LIBFLAGS += $(CURDIR)/libs/GLFW_64/libglfw3.a ## Used full path as linker flag -lglfw3 not recognied
	LIBFLAGS += $(CURDIR)/libs/assimp/libassimp.a ## Used full path as linker flag -lassimp not recognied
	LIBFLAGS += $(CURDIR)/libs/assimp/libzlibstatic.a

	LIBRARYPATHS = -L$(CURDIR)/libs/GLFW_64
else
	## Used full path as linker flag -lglfw3 not recognied
	LIBFLAGS += $(CURDIR)/libs/GLFW_linux/libglfw3.a 
	LIBFLAGS += /usr/lib/x86_64-linux-gnu/libassimp.so
	LIBFLAGS += -lGL -lGLU -lX11 -ldl -pthread## Linux

	LIBRARYPATHS = -L$(CURDIR)/libs/GLFW_linux
endif


# Library DIR and Include DIR
INCLUDEPATHS = -I$(CURDIR)/include
INCLUDEPATHS += -I$(CURDIR)/include/imgui
LIBRARYPATHS = -L$(CURDIR)/libs/assimp

$(info =============================)
$(info CFLAGS : $(CFLAGS))
$(info CXXFLAGS : $(CXXFLAGS))
$(info CC : $(CC))
$(info CXX : $(CXX))
$(info LIBFLAGS : $(LIBFLAGS))
$(info INCLUDEPATHS : $(INCLUDEPATHS))
$(info LIBRARYPATHS : $(LIBRARYPATHS))
$(info =============================)

# make compile
compile: $(TARGET)

#make run
run: compile $(TARGET)
	$(TARGET)

# $^ is prerequisits (c objs and cpp objs)
# $@ is target
$(TARGET) : $(C_OBJECTS) $(CPP_OBJECTS)
	$(CXX) $^ -o $@ $(LIBFLAGS)

# $< evaluates to the first prerequisite
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDEPATHS) -c $< -o $@ 

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDEPATHS) $(LIBRARYPATHS) -c $< -o $@


clean:
	rm -f $(BUILDDIR)/*.o $(TARGET)
