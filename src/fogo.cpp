#include "Projects.hpp"
#include "Utils.hpp"
#include <vector>
#include <raylib.h>

#include <iostream>

namespace fogo {
    struct Particula {
        Vector2 pos;
        Vector2 speed;
        Color color;
        float alpha = 1.0f;
        int otherSpeed;
    };

    std::vector<Particula> particulas;
    bool podeFogah = false;

    void init()
    {

    }

    void update()
    {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && podeFogah) {
            CriaFogo(GetMousePosition());
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) podeFogah = true;

        for (int i=(int) particulas.size() - 1; i>=0; i--) {
            bool inverteu = false;
            Particula* p = &particulas[i];
            p->pos = SumVector2(p->pos, p->speed);
            p->speed.y -= 1;
            p->alpha -= 0.05f * p->otherSpeed;
            if (p->alpha <= 0.5f && !inverteu && p->otherSpeed == 1) {
                inverteu = true;
                p->speed.x *= -1.3;
            }
            if (p->alpha <= 0) particulas.erase(particulas.begin() + i);
        }

        if (IsKeyPressed(KEY_ESCAPE)) reset();
    }

    void draw()
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
        
        for (int i=0; i<(int) particulas.size(); i++) {
            DrawCircleV(particulas[i].pos, 5, Fade(particulas[i].color, particulas[i].alpha));
        }

        DrawText("Clique e segure para criar chamas", 10, 10, 20, LIGHTGRAY);
    }

    void reset()
    {
        particulas.clear();
        podeFogah = false;
    }

    void CriaFogo(Vector2 pos)
    {
        for (int i=0; i<20; i++) { // Bolas cinzas em baixo
            Particula p;
            p.pos = pos;
            p.speed = {GetRandomValue(-5 * 10, 5 * 10) / 10.0f, GetRandomValue(0 * 10, -1 * 10) / 10.0f};
            if (GetRandomValue(0, 1)) p.color = LIGHTGRAY;
            else p.color = DARKGRAY;
            p.otherSpeed = 2;
            particulas.push_back(p);
        }
        for (int i=0; i<40; i++) { // Fogo mesmo
            Particula p;
            p.pos = pos;
            p.speed = {GetRandomValue(-4 * 10, 4 * 10) / 10.0f, GetRandomValue(-3 * 10, -5 * 10) / 10.0f};
            int opa = GetRandomValue(1, 2);
            if (opa == 1) p.color = RED;
            else if (opa == 2) p.color = ORANGE;
            p.otherSpeed = 1;
            particulas.push_back(p);
        }
    }

}