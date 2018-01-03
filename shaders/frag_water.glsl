#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D myText;

void main()
{
    vec4 tmp = texture(myText, TexCoord);
    FragColor = vec4(tmp.rgb, 0.5);
}