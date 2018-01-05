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
    FragColor = vec4(tmp.rgb, 0.8f);
    //FragColor = vec4(0.250, 0.643, 0.874, 0.8);

    vec3 Normals = normalize(cross(dFdx(vertexPos), dFdy(vertexPos)));

    float ratio = 1.00 / 1.33;
    vec3 I = normalize(vertexPos - cameraPos);
    vec3 refraction = refract(I, normalize(-Normals), ratio);
    FragColor *= vec4(texture(skybox, refraction).rgb, 1.0);

    vec3 reflection = reflect(I, normalize(-Normals));
    FragColor *= vec4(texture(skybox, reflection).rgb, 1.0);
}