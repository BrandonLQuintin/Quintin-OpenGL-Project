#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec2 u;
uniform vec2 v;

uniform bool invertColor;
uniform bool blueColor;
uniform bool firstTextureAtlas;

void main()
{
    vec2 uv = vec2(mix(u.x, u.y, TexCoord.x), mix(v.x, v.y, TexCoord.y));
    vec4 texelColor;

    if (firstTextureAtlas){
        texelColor = texture(texture1, uv);
    }

    else{
        texelColor = texture(texture2, uv);
    }

    if (texelColor.a < 0.1f){
        discard;
    }

    if (invertColor){
        texelColor.rgb = vec3(0.5f, 0.0f, 0.0f);
    }
    else if (blueColor){
        texelColor.rgb = vec3(0.0f, 0.0f, 0.5f);
    }
    else {
        texelColor.rgb = vec3(0.9f);
    }

	FragColor = texelColor;
}
