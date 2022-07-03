#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

uniform float x;
uniform float y;
uniform mat4 transform;

out vec3 ourColor;
out vec3 vertPos;
out vec2 TexCoord;

void main()
{
    gl_Position = transform * vec4(aPos.x + sin(x), aPos.y + tan(cos(y)) / 5, tan(aPos.z), 1.0) / 10;
    ourColor = aColor;
    vertPos = vec3(aPos.x + x + .5, aPos.y + y + .5, aPos.z + x + .5);
    TexCoord = aTexCoord;
    //TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    //gl_Position = transform * vec4(aPos, 1.0f);
}