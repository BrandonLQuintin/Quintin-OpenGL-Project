#include "text_render.h"
std::map<char, std::vector<float>> characterUV = {
    {'a', returnTextureUV(0, 0)},
    {'b', returnTextureUV(1, 0)},
    {'c', returnTextureUV(2, 0)},
    {'d', returnTextureUV(3, 0)},
    {'e', returnTextureUV(4, 0)},
    {'f', returnTextureUV(5, 0)},
    {'g', returnTextureUV(6, 0)},
    {'h', returnTextureUV(7, 0)},
    {'i', returnTextureUV(8, 0)},
    {'j', returnTextureUV(9, 0)},
    {'k', returnTextureUV(10, 0)},
    {'l', returnTextureUV(11, 0)},
    {'m', returnTextureUV(12, 0)},
    {'n', returnTextureUV(13, 0)},
    {'o', returnTextureUV(14, 0)},
    {'p', returnTextureUV(15, 0)},
    {'q', returnTextureUV(0, 1)},
    {'r', returnTextureUV(1, 1)},
    {'s', returnTextureUV(2, 1)},
    {'t', returnTextureUV(3, 1)},
    {'u', returnTextureUV(4, 1)},
    {'v', returnTextureUV(5, 1)},
    {'w', returnTextureUV(6, 1)},
    {'x', returnTextureUV(7, 1)},
    {'y', returnTextureUV(8, 1)},
    {'z', returnTextureUV(9, 1)},

    {'.', returnTextureUV(10, 1)},
    {',', returnTextureUV(11, 1)},
    {'?', returnTextureUV(12, 1)},
    {'!', returnTextureUV(13, 1)},
    {':', returnTextureUV(14, 1)},
    {';', returnTextureUV(15, 1)},
    {'(', returnTextureUV(0, 2)},
    {')', returnTextureUV(1, 2)},
    {'/', returnTextureUV(2, 2)},
    {'"', returnTextureUV(3, 2)},
    {'-', returnTextureUV(4, 2)},
    {'_', returnTextureUV(5, 2)},
    {'=', returnTextureUV(6, 2)},

    {'1', returnTextureUV(7, 2)},
    {'2', returnTextureUV(8, 2)},
    {'3', returnTextureUV(9, 2)},
    {'4', returnTextureUV(10, 2)},
    {'5', returnTextureUV(11, 2)},
    {'6', returnTextureUV(12, 2)},
    {'7', returnTextureUV(13, 2)},
    {'8', returnTextureUV(14, 2)},
    {'9', returnTextureUV(15, 2)},
    {'0', returnTextureUV(0, 3)},
    {' ', returnTextureUV(10, 10)},

    {'+', returnTextureUV(0, 4)},
    {'*', returnTextureUV(1, 4)},
    {'<', returnTextureUV(2, 4)},
    {'>', returnTextureUV(3, 4)},
    {'[', returnTextureUV(4, 4)},
    {']', returnTextureUV(5, 4)},
    {'\'', returnTextureUV(6, 4)},
    {'&', returnTextureUV(7, 4)}
};


void renderText(Shader shader, std::string input){
        glDisable(GL_DEPTH_TEST);
        shader.use();
        glBindVertexArray(textVAO);

        float textXOffset = 0;
        float textYOffset = 0;

        // No error checking here!

        for (char c: input){
            textXOffset += 0.023f;
            if (textXOffset > 1.7f){
                textXOffset = 0.023f;
                textYOffset -= 0.1f;
            }
            // render text shadow first
            if (c != '\\'){
                shader.setBool("invertColor", true);
                shader.setFloat("textXOffset", textXOffset + 0.003f);
                shader.setFloat("textYOffset", textYOffset - 0.003f);
                setTextureUV(shader, characterUV[c], true);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
            // then render actual text
            if (c == '\\'){
                textXOffset = 0.0f;
                textYOffset -= 0.1f;
            }
            if (c != '\\'){
                shader.setBool("invertColor", false);
                shader.setFloat("textXOffset", textXOffset);
                shader.setFloat("textYOffset", textYOffset);
                setTextureUV(shader, characterUV[c], true);
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }
        glEnable(GL_DEPTH_TEST);
};
