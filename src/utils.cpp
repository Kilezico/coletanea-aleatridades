#include <raylib.h>
#include "Utils.hpp"

Vector2 SumVector2(Vector2 v1, Vector2 v2)
{
    return {v1.x + v2.x, v1.y + v2.y};
}

Texture2D LoadTextureResized(const char* filePath, int newWidth, int newHeight)
{
    Image img = LoadImage(filePath);
    ImageResize(&img, newWidth, newHeight);
    return LoadTextureFromImage(img);
}


// métodos de Project Button

ProjectButton::ProjectButton(const char* path, Rectangle rect) 
    : printscreen(), rec(rect)
{
    printscreen = LoadTextureResized(path, rec.width, rec.height);
}

bool ProjectButton::wasClicked()
{
    return CheckCollisionPointRec(GetMousePosition(), rec);
}

void ProjectButton::draw()
{
    DrawRectangle(rec.x-margin, rec.y-margin, rec.width+2*margin, rec.height+2*margin, GOLD);
    DrawTexture(printscreen, rec.x, rec.y, WHITE);
}

void ProjectButton::move(int dy)
{
    rec.y += dy;
}

Rectangle ProjectButton::getRec() { return rec; }