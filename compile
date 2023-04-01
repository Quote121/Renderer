# 32 bit executable
gcc -m32 -c -g -I"D:\git\Renderer\include" -o glad.o src/glad.c
i686-w64-mingw32-g++.exe -c -g -std=c++20 -I"D:\git\Renderer\include" -L"D:\git\Renderer\libs\GLFW_32" -o textures.o src/textures.cpp
i686-w64-mingw32-g++.exe -c -g -std=c++20 -I"D:\git\Renderer\include" -L"D:\git\Renderer\libs\GLFW_32" -o stb.o src/stb_image.cpp
i686-w64-mingw32-g++.exe -o tex.exe textures.o glad.o stb.o -lopengl32 "D:\git\Renderer\libs\GLFW_32\libglfw3.a" -lgdi32

# Compiles as a 64 bit executable
#gcc -c -g -I"D:\git\Renderer\include" -o glad.o src/glad.c
#g++ -c -g -std=c++20 -I"D:\git\Renderer\include" -L"D:\git\Renderer\libs\GLFW_64" -o textures.o src/textures.cpp
#g++ -c -g -std=c++20 -I"D:\git\Renderer\include" -L"D:\git\Renderer\libs\GLFW_64" -o stb.o src/stb_image.cpp
#g++ -g -o tex.exe textures.o glad.o stb.o -lopengl32 "D:\git\Renderer\libs\GLFW_64\libglfw3.a" -lgdi32