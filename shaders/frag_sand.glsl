#version 330 core
out vec4 FragColor;

in vec3 vertexPos;
in vec2 TexCoord;

uniform sampler2D myText;

vec4 colorize(vec4 src, vec4 dst)
{
    float c = (src.r + src.g + src.b) / 3;
    return vec4(c, c, c, 1.0) * dst;
}


void main()
{
    FragColor = texture(myText, TexCoord);

    if (vertexPos.y <= 1.5)
        FragColor *= vec4(0.761, 0.698, 0.502, 1.0);
    else if (vertexPos.y > 1.5 && vertexPos.y <= 6)
        FragColor *= vec4(0.172, 0.690, 0.215, 1.0);
    else if (vertexPos.y > 6 && vertexPos.y < 10)
        FragColor *= vec4(0.501, 0.517, 0.529, 1.0);
}