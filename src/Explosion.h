#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "SDL.h"
#include "Constants.h"
#include "Sprite.h"

class Explosion : public Sprite
{
public:
    Explosion()
    {}
    Explosion(SDL_Surface *image, int w, int h, int x, int y, float interval, int total_frames)
        : Sprite(image, w, h, x, y, 0, 0, interval, total_frames),
        alive_(true)
    {}
    ~Explosion()
    {}


    void draw();
    bool alive()        { return alive_;  }
    void kill()         { alive_ = false; }


private:
    bool alive_;
};
#endif //EXPLOSION_H
