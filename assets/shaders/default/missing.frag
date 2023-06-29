#version 460 core

out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D texture1;

void main()
{
    // texture funtion takes the texture and the coords
    FragColor = texture(texture1, TexCoord);
}