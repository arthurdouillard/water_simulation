#version 330 core
out vec4 FragColor;

in vec3 vertexPos;
in vec2 TexCoord;

uniform sampler2D myText;
uniform vec3 cameraPos;

void main()
{
    float dist = distance(vertexPos, cameraPos);

    vec4 tmp = texture(myText, TexCoord);
    FragColor = vec4(tmp.rgb, 0.8f);

    float opacity = clamp(dist / 100, 0, 1);
    FragColor.a *= 1.0 - opacity;
}