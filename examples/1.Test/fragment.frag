#version 460 core
layout(location = 0) in vec3 col;
layout(location = 0) out vec3 fragColor;

void main()
{
	fragColor = col;
}
