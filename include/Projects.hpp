#pragma once
#include <raylib.h>

// Cabeca quicante
namespace cabeca {
    void init();
    void update();
    void draw();
    void reset();
}
// Bolotas

namespace bolas {
    struct Bola {
        Vector2 center;
        float radius;
        float speed;
        float alpha;
        Color color;
    };
    
    void init();
    void update();
    void draw();
    void play();
    void reset();

    void newBall(Bola *bola);
}

namespace fogo {
    void init();
    void update();
    void draw();
    void reset();

    void CriaFogo(Vector2 pos);
}

namespace anim {
    void init();
    void update();
    void draw();
    void reset();

    void updateFrame(int duration);
}