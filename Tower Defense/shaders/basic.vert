#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoords;

smooth out vec3 passColor;
smooth out vec2 passTexCoords;

uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    passColor = color;
	passTexCoords = texCoords;

	vec4 posEyeSpace = view * transform * vec4(position, 1.0);
    gl_Position = projection * vec4(round(posEyeSpace.xyz), posEyeSpace.w);
}
