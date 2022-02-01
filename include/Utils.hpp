#pragma once

#include <raylib.h>
// Objetivo desse arquivo é o de criar definições e funções úteis para o todo

typedef struct {
    Vector2 center;
    float radius;
} Circle;

typedef enum {
    TITLE = 0, MENU, CREDITS, PLAY
} screenLoader;

typedef enum {
    CABECA = 0, BOLAS, FOGO, ANIM
} menuProject;


Vector2 SumVector2(Vector2 v1, Vector2 v2); // Soma dois vetores

Texture2D LoadTextureResized(const char* filePath, int newWidth, int newHeight);

class ProjectButton {
    Texture2D printscreen;
    Rectangle rec;
    int margin = 3;
public:
    ProjectButton(const char* texturePath, Rectangle rec);
    bool wasClicked();
    void draw();
    void move(int dy);
    Rectangle getRec();
};
