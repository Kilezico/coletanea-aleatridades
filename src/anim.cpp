#include "Projects.hpp"
#include "Utils.hpp"

#include <raylib.h>
#include <extras/easings.h>

namespace anim
{
    int animAtual = 0;
    int stage = 0;
    int animCount = 3;
    int frameCounter = 0;

    Vector2 pos;
    int radius;
    float alpha = 1.0f;

    Rectangle playButton;

    void init()
    {
        playButton = {(float) GetScreenWidth()/2-100, (float) GetScreenHeight()/2-30, 200, 60};
    }

    void update()
    {
        // Parte do botão de play e seleção de anims
        if (stage == 0) {
            if (IsKeyPressed(KEY_LEFT)) {
                animAtual--;
                if (animAtual < 0) animAtual = 0;
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                animAtual++;
                if (animAtual >= animCount) animAtual = animCount - 1;
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), playButton)) {
                stage = 1;
            }

            if (animAtual == 0) {
                pos = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
                radius = 0;
            }
        }

        // updates dos anims
        if (animAtual == 0)
        {
            if (stage == 1)
            {
                if (frameCounter > 30 && frameCounter <= 150) radius = EaseElasticOut(frameCounter-30, 0, 60, 120);
                updateFrame(170);
            }
            if (stage == 2) {
                pos.y = EaseQuadOut(frameCounter, GetScreenHeight()/2, -100, 30);
                updateFrame(30);
            }
            if (stage == 3) {
                if (frameCounter <= 90) pos.y = EaseCubicIn(frameCounter, GetScreenHeight()/2 - 100, GetScreenHeight()/2-radius + 100, 90);
                updateFrame(100);
            }
            if (stage == 4) {
                if (frameCounter <= 60) pos.x = EaseSineOut(frameCounter, GetScreenWidth()/2, 250, 60);
                updateFrame(90);
            }
            if (stage == 5) {
                if (frameCounter <= 90) pos.x = EaseSineOut(frameCounter, GetScreenWidth()/2+250, -500, 90);
                updateFrame(120);
            }
            if (stage == 6) {
                updateFrame(120);
            }
            if (stage == 7) {
                pos.x = EaseBackInOut(frameCounter, GetScreenWidth()/2-250, 250, 120);
                pos.y = EaseBackInOut(frameCounter, GetScreenHeight() - radius, GetScreenHeight() / 2 - GetScreenHeight() + radius, 120);
                updateFrame(120);
            }
            if (stage == 8) {
                updateFrame(60);
            }
            if (stage == 9) {
                radius = EaseBounceIn(frameCounter, 60, GetScreenHeight(), 90);
                updateFrame(90);
            }
            if (stage == 10) {
                if (frameCounter <= 30) alpha = EaseLinearNone(frameCounter, 1.0f, -1.0f, 30);
                updateFrame(90);
            }
            if (stage == 11) {
                stage = 0;
                alpha = 1.0f;
            }
        }

        // Resetação
        if (IsKeyPressed(KEY_ESCAPE)) reset();
    }

    void draw()
    {
        if (stage == 0) {
            DrawRectangleRec(playButton, GRAY);
            DrawRectangle(playButton.x+3, playButton.y+3, playButton.width-6, playButton.height-6, RED);
            DrawText("PLAY", GetScreenWidth()/2 - 29, GetScreenHeight()/2 - 10, 25, DARKGRAY);
            DrawText(TextFormat("Animação selecionada: %d", animAtual+1), GetScreenWidth()/2 - 137, 130, 25, DARKGRAY);
        }
        if (animAtual == 0) 
        {
            if (stage >= 1 && stage < 6) {
                DrawCircleV(pos, radius, RED);
            }
            if (stage >= 6) {
                DrawCircle(pos.x + GetRandomValue(-2, 2), pos.y + GetRandomValue(-2, 2), radius, Fade(RED, alpha));
            }
            
            
            
        }
        

        
    }

    void reset()
    {
        frameCounter = 0;
        animAtual = 0;
        stage = 0;
    }

    void updateFrame(int duration) 
    {
        frameCounter++;
        if (frameCounter >= duration) {
            frameCounter = 0;
            stage += 1;
        }
    }

};
