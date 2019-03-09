#include "Bullet.h"
#include "Engine.h"

Bullet::Bullet(SDL_Surface *image, Direction direction, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval)
    : Sprite(image, w, h, x, y, x_velocity, y_velocity, interval, 1),
    direction_(direction),
    alive_(true)
{
    //don't create a bullet in the engine constructor
    Engine *engine = Engine::get_instance();

    //create the bitmasks
    SDL_Rect mask;
        mask.h = h;
        mask.w = w;
        mask.x = 0;
        mask.y = 0;

    bitmask_ = engine->create_bitmask(image, mask);
}



void Bullet::draw()
{
    if(animating_ == 1)
    {
        if(last_update_ + interval_ < SDL_GetTicks())
        {
            if(direction_ == up) move_up();
            else move_down();

            //check if beyond the screen, if it is, kill it
            if(x_ > SCREEN_WIDTH || x_ + w_ < 0 || y_ > SCREEN_HEIGHT || y_ + h_ < 0)
                alive_ = false;

            last_update_ = SDL_GetTicks();
        }
    }

    SDL_Rect from;
        from.x = 0;
        from.y = 0;
        from.w = w_;
        from.h = h_;
    SDL_Rect to;
        to.x = x_;
        to.y = y_;

    SDL_Surface *screen = SDL_GetVideoSurface();
    SDL_BlitSurface(image_, &from, screen, &to);
}
