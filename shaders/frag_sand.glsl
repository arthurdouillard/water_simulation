#version 330 core
out vec4 FragColor;

in vec3 vertexPos;
in vec2 TexCoord;

uniform sampler2D myText;
uniform vec3 cameraPos;

void main()
{
    FragColor = texture(myText, TexCoord);

    float dist = distance(vertexPos, cameraPos);
    float opacity = clamp(dist / 100, 0, 1);
    FragColor.a *= 1.0 - opacity;
}