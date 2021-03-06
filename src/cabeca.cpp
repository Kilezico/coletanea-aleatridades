#include <raylib.h>

#include "Projects.hpp"
#include "Utils.hpp"

#include <iostream>

namespace cabeca {
    Vector2 position = {100, 100};
    Vector2 speed = {4, 5};
    Rectangle source = {0, 0, 100, 100};
    Texture2D euconut;

    void init()
    {
        Image euconutImg = LoadImage("res/euconut.png");
        ImageResize(&euconutImg, 100, 100);
        euconut = LoadTextureFromImage(euconutImg);
    }


    void update()
    {
        position = SumVector2(position, speed);

        if (position.x + speed.x <= 0 || position.x + euconut.width + speed.x >= GetScreenWidth()) {
            speed.x *= -1;
            source.width *= -1;
        }
        if (position.y + speed.y <= 0 || position.y + euconut.height + speed.y >= GetScreenHeight()) {
            speed.y *= -1;
            source.height *= -1;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            speed.x *= 1.5;
            speed.y *= 1.5;

            if (speed.x >= 20 || speed.x <= -20) speed = {
                speed.x < 0 ? -4.0f : 4.0f,
                speed.y < 0 ? -5.0f : 4.0f
            };
        }

        if (IsKeyPressed(KEY_ESCAPE)) reset();
    } 

    void draw() 
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        
        DrawTextureRec(euconut, source, position, WHITE);

        DrawText("Pressione ESC para sair.", 10, 10, 20, LIGHTGRAY);
        DrawText("Clique na tela para mudar a velocidade", 10, 35, 20, LIGHTGRAY);
    }

    void reset() {
        position = {100, 100};
        speed = {4, 5};
    }
}