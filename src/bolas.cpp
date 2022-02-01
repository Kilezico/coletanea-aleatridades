#include "Projects.hpp"
#include "Utils.hpp"
#include <raylib.h>

#include <string>
#include <vector>

#define MAX_BOLAS 50


namespace bolas {
    Color bolaCores[7] = {
        RED,
        ORANGE,
        YELLOW,
        GREEN,
        BLUE,
        DARKBLUE,
        VIOLET
    };
    
    std::vector<Music> musicas;
    int musicaAtual = 0;
    int musicBarTimePassed = 0;
    bool pause = false;
    float pitch = 1.0f;

    int frameCount = 0;

    Bola bolas[MAX_BOLAS];

    void init()
    {
        for(int i=0; i<MAX_BOLAS; i++) {
            newBall(&bolas[i]);
        }

        musicas.push_back(LoadMusicStream("res/bolasMusica1.mp3"));
        SetMusicVolume(musicas[0], 0.5);
        musicas.push_back(LoadMusicStream("res/bolasMusica2.mp3"));
        musicas.push_back(LoadMusicStream("res/bolasMusica3.mp3"));
        musicas.push_back(LoadMusicStream("res/bolasMusica4.mp3"));

        for (int i=0; i<(int) musicas.size(); i++) {
            musicas[i].looping = false;
        }
    
        play();
    }
    
    void update()
    {
        if (!pause) {
            
            UpdateMusicStream(musicas[musicaAtual]);
            SetMusicPitch(musicas[musicaAtual], pitch);

            for (int i=0; i<MAX_BOLAS; i++) {
                bolas[i].radius += bolas[i].speed / 10;
                bolas[i].alpha += bolas[i].speed / 200.0f;

                if (bolas[i].alpha >= 1.0f) { // A bola já está no seu tamanho máximo e totalmente opaca
                    bolas[i].speed *= -1;
                }
                if (bolas[i].alpha < 0.0f) { // A bola já esteve opaca e agora voltou até a estado inicial
                    newBall(&bolas[i]);
                }
            }
            
            musicBarTimePassed = GetMusicTimePlayed(musicas[musicaAtual]) / GetMusicTimeLength(musicas[musicaAtual]) * (GetScreenWidth() - 40);        
            if (!IsMusicStreamPlaying(musicas[musicaAtual])) musicBarTimePassed = GetScreenWidth() - 40;

            // Troca música
            if (IsKeyPressed(KEY_LEFT)) {
                StopMusicStream(musicas[musicaAtual]);
                musicaAtual--;
                if (musicaAtual < 0) musicaAtual = (int) musicas.size() - 1;
                PlayMusicStream(musicas[musicaAtual]);
            }
            if (IsKeyPressed(KEY_RIGHT)) {
                StopMusicStream(musicas[musicaAtual]);
                musicaAtual++;
                if (musicaAtual >= (int) musicas.size()) musicaAtual = 0;
                PlayMusicStream(musicas[musicaAtual]);
            }

            // Altera o pitch
            if (IsKeyDown(KEY_UP)) {
                pitch += 0.01;
                if (pitch > 1.5f) pitch = 1.5f;

            }
            if (IsKeyDown(KEY_DOWN)) {
                pitch -= 0.01;
                if (pitch <= 0.5) pitch = 0.5;

            }
            if (IsKeyPressed(KEY_R)) pitch = 1.0f;
        } else {
            frameCount++;
            if (frameCount >= 60) frameCount = 0;
        }

        

        if (IsKeyPressed(KEY_ESCAPE)) {
            reset();
        }
        if (IsKeyPressed(KEY_P)) pause = !pause;
    }

    void draw()
    {
        for (int i=0; i<MAX_BOLAS; i++) {
            DrawCircleV(bolas[i].center, bolas[i].radius, Fade(bolas[i].color, bolas[i].alpha));
        }

        // Tempo da música (barrinha)
        DrawRectangle(20, GetScreenHeight() - 35, GetScreenWidth() - 40, 15, LIGHTGRAY);
        DrawRectangle(20, GetScreenHeight() - 35, musicBarTimePassed, 15, RED);
        DrawRectangleLines(20, GetScreenHeight() - 35, GetScreenWidth() - 40, 15, GRAY);
    
        // Controllos
        DrawText("Controles:", 15, 15, 15, BLACK);
        DrawText("P -> Pausar", 15, 35, 10, BLACK);
        DrawText("Setas esquerda/direita -> Mudar de música", 15, 50 , 10, BLACK);
        DrawText("Setas cima/baixo -> Mudar a altura", 15, 65, 10, BLACK);
        DrawText("R -> Restora altura original", 15, 80, 10, BLACK);
        DrawText("Esc -> Sai das Bolas Dançantes", 15, 95, 10, BLACK);
        
        DrawRectangleLines(10, 10, 240, 100, DARKBLUE);
        DrawRectangle(10, 10, 240, 100, Fade(BLUE, 0.2f));
        
        DrawText(TextFormat("Música: %d", musicaAtual+1), GetScreenWidth() - 100, 10, 15, DARKGRAY);
        
        if (pitch >= 1.5) DrawText("Altura: MÁXIMO", GetScreenWidth() - 120, 25, 15, DARKGRAY);
        else if (pitch <= 0.5) DrawText("Altura: MÍNIMO", GetScreenWidth() - 120, 25, 15, DARKGRAY);
        else DrawText(TextFormat("Altura: %.2f", pitch), GetScreenWidth() - 100, 25, 15, DARKGRAY);

        if (pause && (frameCount/30) % 2) DrawText("PAUSADO", 350, 200, 25, LIGHTGRAY);

    }

    void play()
    {
        PlayMusicStream(musicas[0]);
    }

    void reset()
    {
        for (int i=0; i<MAX_BOLAS; i++) {
            newBall(&bolas[i]);
        }

        for (int i=0; i< (int) musicas.size(); i++) {
            StopMusicStream(musicas[i]);
        }

        musicaAtual = 0;
        pause = false;
        pitch = 1.0f;
    }

    void newBall(Bola *bola) {
        bola->radius = GetRandomValue(20, 40);
        bola->center = {
            (float) GetRandomValue(bola->radius, GetScreenWidth() - bola->radius),
            (float) GetRandomValue(bola->radius, GetScreenHeight() - bola->radius)    
        };
        bola->alpha = 0.0f;
        bola->speed = GetRandomValue(5, 8);
        bola->color = bolaCores[GetRandomValue(0, 6)];
    }

}