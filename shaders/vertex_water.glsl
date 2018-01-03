#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

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

	float speed = 2.0f;
	float amount = 1.0f;
	float height = 0.1f;

	float y = sin(time * speed + (aPos.x * aPos.z * amount)) * height;
 //   float zz = (2 * sin(20 * sqrt(xx + yy) - 4 * time) + rand(xx, yy)) / 10;
	gl_Position = projection * view * vec4(aPos.x, y, aPos.z, 1.0f);

	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}