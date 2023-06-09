#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 localPos = vec3(1.0, 0.0, 0.0);

void main()
{
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos+localPos, 1.0);
}