#version 330

smooth in vec4 theColor;

uniform float time;

out vec4 outputColor;

const vec4 firstColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);

void main()
{
	outputColor = theColor;
}
