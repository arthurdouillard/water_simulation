#version 330 core
out vec4 FragColor;

in vec3 vertexPos;
in vec2 TexCoord;

uniform sampler2D myText;
uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{
    vec4 tmp = texture(myText, TexCoord);
    FragColor = vec4(tmp.rgb, 1.0f);

    vec3 Normals = normalize(cross(dFdx(vertexPos), dFdy(vertexPos)));

    float ratio = 1.00 / 1.33;
    vec3 I = normalize(vertexPos - cameraPos);
    vec3 R = refract(I, normalize(-Normals), ratio);
    FragColor *= vec4(texture(skybox, R).rgb, 1.0);
}