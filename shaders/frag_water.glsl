#version 330 core
out vec4 FragColor;

in vec3 vertexPos;
in vec2 TexCoord;

uniform sampler2D TexWater;
uniform samplerCube skybox;
uniform vec3 cameraPos;

void main()
{
    vec4 tmp = texture(TexWater, TexCoord);
    FragColor = vec4(tmp.rgb, 0.9f);

    vec3 Normals = normalize(cross(dFdx(vertexPos), dFdy(vertexPos)));

    float ratio = 1.00 / 1.33;
    vec3 I = normalize(vertexPos - cameraPos);
    vec3 refraction = refract(I, normalize(-Normals), ratio);
    FragColor *= vec4(texture(skybox, refraction).rgb, 1.0);

    vec3 reflection = reflect(I, normalize(-Normals));
    FragColor *= vec4(texture(skybox, reflection).rgb, 1.0);

    vec3 diffuse = vec3(-1.0, -1.0, -1.0);
    float attenuation =  dot(-normalize(cross(dFdx(vertexPos), dFdy(vertexPos))), diffuse);
    attenuation = max(attenuation, 0.0);

    vec3 hazy_ambiant = 0.4 * vec3(0.741, 0.745, 0.752);
    vec3 sunrise_ambiant = 0.4 * vec3(0.713, 0.494, 0.356);

    FragColor.xyz *= (hazy_ambiant + attenuation);
    FragColor.a = 0.9;

}