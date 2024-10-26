#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform float textXOffset;
uniform float textYOffset;

void main()
{
    vec4 textPosition = vec4(aPos, 1.0);
    textPosition.x += -0.98f + textXOffset;
    textPosition.y += 0.95f + textYOffset;

    gl_Position = textPosition;

    TexCoord = aTexCoord;
}
