#include "Projects.hpp"
#include "Utils.hpp"

#include <raylib.h>
#include <extras/easings.h>

#include <iostream>

namespace anim
{
    // Variáveis para tudo
    int animAtual = 0;
    int stage = 0;
    int animCount = 2;
    int frameCounter = 0;

    // Variáveis para anims
    Vector2 pos;
    int radius;
    float alpha;
    
    Rectangle rect;
    float rotation;
    Vector2 origin;
    Texture2D euconut;

    Rectangle playButton;

    void init()
    {
        playButton = {(float) GetScreenWidth()/2-100, (float) GetScreenHeight()/2-30, 200, 60};
        euconut = LoadTexture("res/euconut.png");
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
                alpha = 1.0f;
            }
            if (animAtual == 1) {
                rect = {-100, 125, 100, 100};
                rotation = 0.0f;
                origin = {50, 50};
                alpha = 1.0f;
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
                if (frameCounter <= 70) pos.y = EaseQuadIn(frameCounter, GetScreenHeight()/2 - 100, GetScreenHeight()/2-radius + 100, 70);
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
                radius = EaseBounceIn(frameCounter, 60, 500, 180);
                updateFrame(180);
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
        if (animAtual == 1)
        {
            if (stage == 1) {
                rect.x = EaseLinearNone(frameCounter, -100, GetScreenWidth() + 200, 120);
                rotation = EaseLinearNone(frameCounter, 0, 360 * 2, 120);
                updateFrame(120);
                if (frameCounter <= 0) {
                    rect.y += 100;
                    SetShapesTexture(euconut, {0, 0, (float) euconut.width, (float) euconut.height});
                }
            }
            if (stage == 2) {
                rect.x = EaseLinearNone(frameCounter, GetScreenWidth() + 100, -GetScreenWidth() - 200, 120);
                rotation = EaseLinearNone(frameCounter, 0, -(360*2), 120);
                updateFrame(120);
                if (frameCounter <= 0) {
                    rect.y += 100;
                    SetShapesTexture(euconut, {0, 0, 0, 0});
                }
            }
            if (stage == 3) {
                rect.x = EaseLinearNone(frameCounter, -100, GetScreenWidth() + 200, 120);
                rotation = EaseLinearNone(frameCounter, 0, 360 * 2, 120);
                updateFrame(120);
                if (frameCounter <= 0) {
                    origin = {0, 100};
                    rect.x = GetScreenWidth();
                }
            }
            if (stage == 4) { // Inclina indo
                if (frameCounter <= 15) {
                    rotation = EaseSineIn(frameCounter, 0, -45, 15);
                    rect.x = EaseSineIn(frameCounter, GetScreenWidth(), -10, 15);
                }
                updateFrame(100);
            }
            if (stage == 5) { // Inclina voltando
                rotation = EaseSineOut(frameCounter, -45, 45, 15);
                rect.x = EaseSineOut(frameCounter, GetScreenWidth()-10, 10, 15);
                updateFrame(15);
                if (frameCounter <= 0) {
                    rect.y -= 150;
                    origin = {100, 100};
                    rect.x = -100;
                }
            }
            if (stage == 6) { // Inclina indo
                if (frameCounter <= 15) {
                    rotation = EaseSineIn(frameCounter, 0, 45, 15);
                    rect.x = EaseSineIn(frameCounter, 0, 10, 15);
                }
                updateFrame(100);
            }
            if (stage == 7) { // Inclina voltando
                rotation = EaseSineOut(frameCounter, 45, -45, 15);
                rect.x = EaseSineOut(frameCounter, 10, -10, 15);
                updateFrame(15);
                if (frameCounter <= 0) {
                    origin = {50, 50};
                    rect.x = GetScreenWidth()/2;
                }
            }
            if (stage == 8) {
                if (frameCounter <= 120) rect.y = EaseBounceOut(frameCounter, -500, GetScreenHeight() + 450, 120);
                updateFrame(140);
            }
            if (stage == 9) { // Aumenta width
                rect.width = EaseSineIn(frameCounter, 100, 400, 50);
                origin = {rect.width/2, rect.height/2};
                updateFrame(50);
            }
            if (stage == 10) { // Diminui width
                rect.width = EaseSineOut(frameCounter, 500, -400, 50);
                origin = {rect.width/2, rect.height/2};
                updateFrame(50);
            }
            if (stage == 11) { // aumenta altura
                rect.height = EaseSineIn(frameCounter, 100, GetScreenWidth() - 50, 60);
                rect.y = EaseSineIn(frameCounter, GetScreenHeight()-50, -GetScreenHeight()/2 + 50, 60);
                origin = {rect.width/2, rect.height/2};
                updateFrame(60);
            }
            if (stage == 12) { // cobre tela
                rect.width = EaseCubicIn(frameCounter, 100, GetScreenWidth() - 100, 90);
                origin = {rect.width/2, rect.height/2};
                updateFrame(90);
            }
            if (stage == 13) { // some
                alpha = EaseLinearNone(frameCounter, 1, -1, 60);
                updateFrame(60);
                if (frameCounter <= 0) stage = 0;
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
        if (animAtual == 1) 
        {
            if (stage >= 1) {
                DrawRectanglePro(rect, origin, rotation, Fade(RED, alpha));
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
        if (frameCounter > duration) {
            frameCounter = 0;
            stage += 1;
        }
    }

};
