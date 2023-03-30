gcc -c -g -I"D:\git\Renderer\include" -o glad.o src/glad.c
g++ -c -g -std=c++20 -I"D:\git\Renderer\include" -I"C:\msys64\mingw64\include" -L"D:\git\Renderer\libs\GLFW_32" -L"C:\msys64\mingw64\lib" -o textures.o src/textures.cpp
g++ -c -g -std=c++20 -I"D:\git\Renderer\include" -I"C:\msys64\mingw64\include" -L"D:\git\Renderer\libs\GLFW_32" -L"C:\msys64\mingw64\lib" -o stb.o src/stb_image.cpp
g++ -g -o tex.exe textures.o glad.o stb.o -lopengl32 "D:\git\Renderer\libs\GLFW_32\libglfw3.a" -lgdi32