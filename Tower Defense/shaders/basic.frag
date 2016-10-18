#version 330

smooth in vec3 passColor;
smooth in vec2 passTexCoords;

out vec4 outputColor;

uniform sampler2D tex;

void main()
{
	outputColor = texture(tex, passTexCoords);// * vec4(passColor, 1.0f);
}
