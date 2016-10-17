#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

smooth out vec4 theColor;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    theColor = color;
	vec4 posEyeSpace = view * transform * vec4(position, 1.0);
    gl_Position = projection * vec4(round(posEyeSpace.xyz), posEyeSpace.w);
}
