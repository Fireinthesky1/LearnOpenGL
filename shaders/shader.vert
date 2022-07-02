#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float x;
uniform float y;

out vec3 ourColor;
out vec3 vertPos;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos.x + x, aPos.y + y, aPos.z, 1.0);
    ourColor = aColor;
    vertPos = vec3(aPos.x + x + .5, aPos.y + y + .5, aPos.z + x + .5);
    TexCoord = aTexCoord;
}