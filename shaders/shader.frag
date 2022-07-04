#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec3 vertPos;
in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float mixValue;

void main()
{
	vec2 translation = vec2(TexCoord.x, TexCoord.y);
	FragColor = mix(texture(texture0, translation), texture(texture1, translation), mixValue);
};