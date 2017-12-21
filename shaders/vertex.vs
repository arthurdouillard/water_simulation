#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 view;
uniform mat4 projection;
uniform float time;

float rand(float x, float y){
	vec2 tmp = vec2(x, y);
    return fract(sin(dot(tmp ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	float xx = (aPos.x-3) * (aPos.x-3);
	float yy = (aPos.y+1) * (aPos.y+1);

	gl_Position = projection * view * vec4(aPos.x,
										   (2 * sin(20 * sqrt(xx + yy) - 4 * time) + rand(xx, yy)) / 10,
										   aPos.z,
										   1.0f);
}