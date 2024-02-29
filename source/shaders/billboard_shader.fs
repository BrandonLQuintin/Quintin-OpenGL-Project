#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec2 u;
uniform vec2 v;

uniform bool firstTextureAtlas;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // ambient
    float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 13);
    vec3 specular = specularStrength * spec * lightColor;

    vec2 uv = vec2(mix(u.x, u.y, TexCoord.x), mix(v.x, v.y, TexCoord.y));
    vec4 texelColor;


    if (firstTextureAtlas){
        texelColor = texture(texture1, uv);
    }

    else{
        texelColor = texture(texture2, uv);
    }

    if (texelColor.a < 0.1){
        discard;
    }

    vec3 result = (ambient + diffuse + specular) * objectColor * texelColor.rgb;

    FragColor = vec4(result, 1.0);
}
