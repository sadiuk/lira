#version 460 core
layout(location = 0) in vec2 pos;
layout(location = 1) in vec3 color;
layout(location = 0) out vec3 fragColor;

uniform float rand;
out gl_PerVertex
{
  vec4 gl_Position;
  float gl_PointSize;
  float gl_ClipDistance[];
};

void main()
{
	fragColor = color * rand;
	gl_Position = vec4(pos.x + 0.5 * gl_InstanceID, pos.y, 0, 1);
}