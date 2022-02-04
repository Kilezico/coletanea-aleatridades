#include <raylib.h>
#include <iostream>
#include <vector> 

#include "Utils.hpp"
#include "Projects.hpp"


int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "Pequena coletânea de coisas legais para vermos se vai funcionar");
    
    SetExitKey(KEY_NULL);

    InitAudioDevice();

    
    // Variáveis gerais, para tudo
    screenLoader currentScreen = TITLE;
    menuProject currentProject; 

    Sound clickSound = LoadSound("res/click.wav");
    SetSoundVolume(clickSound, 0.6f);

    // Variáveis para a tela de título
    Texture2D titleBackground = LoadTexture("res/background.png");
    Rectangle titleButton1 = {(screenWidth - 297) / 2, 205, 298, 61};
    Rectangle titleButton2 = {(screenWidth - 297) / 2, 307, 298, 61};
    
    // Variáveis para a tela de menu das aleatridades'  
    // Texture2D menuBackground = LoadTexture("res/menu.png");
    Image menuBackgroundImg = LoadImage("res/menu.png");
    ImageDrawRectangle(&menuBackgroundImg, screenWidth/2-265, screenHeight/2-140, 530, 280, BLANK);
    Texture2D menuBackground = LoadTextureFromImage(menuBackgroundImg);
    int menuScrollDist = 0;
    std::vector<ProjectButton*> menuButtons;
    
    ProjectButton projCabeca = ProjectButton("res/cabeca.png", {screenWidth/2-230, 100, 200, 112});
    menuButtons.push_back(&projCabeca);
    
    ProjectButton projBolas = ProjectButton("res/bolas.png", {screenWidth/2+30, 100, 200, 112});
    menuButtons.push_back(&projBolas);
    
    ProjectButton projFogo = ProjectButton("res/fogo.png", {screenWidth/2-230, 250, 200, 112});
    menuButtons.push_back(&projFogo);

    ProjectButton projAnim = ProjectButton("res/anim.png", {screenWidth/2+30, 250, 200, 112});
    menuButtons.push_back(&projAnim);

    Rectangle menuButton1 = {(screenWidth - 239) / 2, 380, 240, 50};
    
    

    // Variáveis para a tela de créditos
    Texture2D creditsBackground = LoadTexture("res/credits.png");
    Texture2D creditsTxt = LoadTextureResized("res/creditsTxt.png", 350, 100);
    
    rename("res/.soundbololo.mp3", "res/soundbololo.png");
    Texture2D euconutWide = LoadTextureResized("res/soundbololo.png", 350, 90);    
    rename("res/soundbololo.png", "res/.soundbololo.mp3");
    
    Rectangle creditsButton1 = {(screenWidth - 239) / 2, 380, 240, 50};
    Circle creditsButton2 = {{473, 79}, 14};
    bool creditsMostra = false;

    // Init dos projetos
    cabeca::init();
    bolas::init();
    fogo::init();
    anim::init();

    // Vector2 debugPos = {(screenWidth - 239) / 2, 0};
    // Vector2 debugSize = {240, 50};
    // int debugRadius = 10;

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        switch (currentScreen)
        {
            case TITLE:
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(GetMousePosition(), titleButton1)) {
                        currentScreen = MENU;
                        PlaySound(clickSound);
                    }
                    if (CheckCollisionPointRec(GetMousePosition(), titleButton2)) {
                        currentScreen = CREDITS;
                        PlaySound(clickSound);
                    }
                }
            } break;
            case CREDITS:
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    if (CheckCollisionPointRec(GetMousePosition(), creditsButton1)) {
                        currentScreen = TITLE;
                        creditsMostra = false;
                        PlaySound(clickSound);
                    }
                    if (CheckCollisionPointCircle(GetMousePosition(), creditsButton2.center, creditsButton2.radius)) {
                        creditsMostra = true;
                        PlaySound(clickSound);
                    }
                }
            } break;
            case MENU:
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    Vector2 mousePos = GetMousePosition();
                    if (CheckCollisionPointRec(mousePos, menuButton1)) {
                        currentScreen = TITLE;
                        PlaySound(clickSound);
                    }
                    if (projCabeca.wasClicked()) {
                        currentScreen = PLAY;
                        currentProject = CABECA;
                        PlaySound(clickSound);
                    }
                    if (projBolas.wasClicked()) {
                        currentScreen = PLAY;
                        currentProject = BOLAS;
                        bolas::play();
                        PlaySound(clickSound);
                    }
                    if (projFogo.wasClicked()) {
                        currentScreen = PLAY;
                        currentProject = FOGO;
                        PlaySound(clickSound);
                    }
                    if (projAnim.wasClicked()) {
                        currentScreen = PLAY;
                        currentProject = ANIM;
                        PlaySound(clickSound);
                    }
                }
                if (GetMouseWheelMove() > 0) {
                    menuScrollDist -= 10;
                    for (int i=0; i<(int) menuButtons.size(); i++) {
                        if (menuScrollDist > 0) menuButtons[i]->move(10);
                    }
                    if (menuScrollDist < 0) menuScrollDist = 0;
                    
                }
                if (GetMouseWheelMove() < 0) {
                    menuScrollDist += 10;
                    for (int i=0; i<(int) menuButtons.size(); i++) {
                        if (menuScrollDist < 100) menuButtons[i]->move(-10);
                    }
                    if (menuScrollDist > 100) menuScrollDist = 100;
                }
            } break;
            case PLAY:
            {
                if (IsKeyPressed(KEY_ESCAPE)) {
                    currentScreen = MENU;
                }
                
                switch (currentProject) {
                    case CABECA:
                    {
                        cabeca::update();
                    } break;
                    case BOLAS:
                    {
                        bolas::update();
                    } break;
                    case FOGO:
                    {
                        fogo::update();
                    } break;
                    case ANIM:
                    {
                        anim::update();
                    } break;
                    default: break;
                    
                }
            } break;
            default: break;
        }


        // // Print debugPos
        // if (IsKeyPressed(KEY_SPACE)) printf("debugPos: %.2f, %.2f. Raio: %d\n", debugPos.x, debugPos.y, debugRadius);
        
        // // Funções para cima/baixo
        // if (IsKeyDown(KEY_W)) debugPos.y -= 1;
        // if (IsKeyDown(KEY_S)) debugPos.y += 1;
        // if (IsKeyPressed(KEY_UP)) debugPos.y -= 1;
        // if (IsKeyPressed(KEY_DOWN)) debugPos.y += 1;
        
        // // Funcões para mexer direita/esquerda
        // if (IsKeyDown(KEY_A)) debugPos.x -= 1;
        // if (IsKeyDown(KEY_D)) debugPos.x += 1;
        // if (IsKeyPressed(KEY_LEFT)) debugPos.x -= 1;
        // if (IsKeyPressed(KEY_RIGHT)) debugPos.x += 1;
        
        // if (IsKeyPressed(KEY_T)) debugRadius++;
        // if (IsKeyPressed(KEY_G)) debugRadius--;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (currentScreen)
        {
            case TITLE:
            {
                DrawTexture(titleBackground,0, 0, WHITE);
                
                // 297 61
            } break;
            case CREDITS:
            {
                DrawTexture(creditsBackground, 0, 0, WHITE);

                DrawRectangle(screenWidth/2 - 370/2, 106, 370, 260, ORANGE);

                DrawTexture(creditsTxt, screenWidth/2-175, 130, BLACK);
                if (creditsMostra) DrawTexture(euconutWide, screenWidth/2 - 350/2, screenHeight/2 + 20, WHITE);
                
                // Coiso do Raylib
                DrawText("powered by", screenWidth - 90, screenHeight - 95 - 12, 12, LIGHTGRAY);
                DrawRectangle(screenWidth - 90, screenHeight - 90, 80, 80, BLACK);
                DrawRectangle(screenWidth - 85, screenHeight - 85, 70, 70, RAYWHITE);
                DrawText("raylib", screenWidth - 60, screenHeight - 33, 16, BLACK);
            } break;
            case MENU:
            {

                DrawRectangle(screenWidth/2-265, screenHeight/2-140, 530, 280, ORANGE);

                for (ProjectButton* p : menuButtons) {
                    p->draw();
                }

                DrawTexture(menuBackground, 0, 0, WHITE); // Image tem um buraco transparente para poder aparecer o butões, e ter rolamentos

            } break;
            case PLAY:
            {
                switch (currentProject) {
                    case CABECA:
                    {
                        cabeca::draw();
                    } break;
                    case BOLAS:
                    {
                        bolas::draw();   
                    } break;
                    case FOGO:
                    {
                        fogo::draw();
                    } break;
                    case ANIM:
                    {
                        anim::draw();
                    } break;
                    default: break;
                }
            } break;
            default: break;
        }

        EndDrawing();

    }

    UnloadSound(clickSound);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}