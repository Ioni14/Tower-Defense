#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

smooth out vec4 theColor;

uniform mat4 transform;

void main()
{
    theColor = color;
    gl_Position = transform * vec4(position, 1.0);
}
