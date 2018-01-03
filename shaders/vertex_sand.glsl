#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 vertexPos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vertexPos = aPos;

    gl_Position = projection * view * vec4(aPos.xyz, 1.0f);
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}