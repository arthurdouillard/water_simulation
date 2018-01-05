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

    vec3 diffuse = vec3(-1.0, -1.0, -1.0);
    float attenuation =  dot(-normalize(cross(dFdx(vertexPos), dFdy(vertexPos))), diffuse);
    attenuation = max(attenuation, 0.0);

    vec3 hazy_ambiant = 0.4 * vec3(0.741, 0.745, 0.752);
    vec3 sunrise_ambiant = 0.4 * vec3(0.713, 0.494, 0.356);

    FragColor.xyz *= (hazy_ambiant + attenuation);
    FragColor.a = 1.0;
}