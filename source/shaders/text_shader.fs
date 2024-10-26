#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture2;

uniform vec2 u;
uniform vec2 v;

uniform bool blueColor;
uniform bool firstTextureAtlas;

void main()
{
    vec2 glyphUV = vec2(mix(u.x, u.y, TexCoord.x), mix(v.x, v.y, TexCoord.y));

    vec2 glyphSizeUV = vec2(u.y - u.x, v.y - v.x);

    vec2 shadowOffsetUV = glyphSizeUV * vec2(0.15f, -0.01f);

    vec2 uvShadow = clamp(glyphUV + shadowOffsetUV, vec2(u.x, v.x), vec2(u.y, v.y));

    vec4 texelColor;
    vec4 shadowTexel;

    texelColor = texture(texture2, glyphUV);
    shadowTexel = texture(texture2, uvShadow);

    vec4 finalColor;

    if (shadowTexel.a > 0.1f){
        // render the main text
        finalColor = vec4(0.9f, 0.9f, 0.9f, shadowTexel.a);
    }
    else if (texelColor.a > 0.1f){
        // Render the main text
        vec3 color = vec3(0.5f, 0.0f, 0.0f);
        if (blueColor){
            color = vec3(0.0f, 0.0f, 0.5f);
        }

        finalColor = vec4(color, texelColor.a);
    }
    else{
        discard;
    }

    FragColor = finalColor;
}
