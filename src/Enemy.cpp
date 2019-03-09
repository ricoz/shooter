#include "Enemy.h"
#include "Engine.h"

Enemy::Enemy(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames)
: Vehicle(image, w, h, x, y, x_velocity, y_velocity, interval, total_frames)
{}



Enemy::~Enemy()
{}



void Enemy::draw()
{
    if(animating_ == 1)
    {
        //kill when enemy is beyond the screen
        //note to self: problem when instantiating enemies beyond the screen
        if(x_ > SCREEN_WIDTH || x_ + w_ < 0 || y_ > SCREEN_HEIGHT || y_ + h_ < 0)
            alive_ = false;

        if(last_update_ + interval_ < SDL_GetTicks())
        {
            frame_++;
            if(frame_ > total_frames_ - 1) frame_ = 0;
            last_update_ = SDL_GetTicks();
        }
    }

    SDL_Rect from;
        from.x = frame_ * w_;
        from.y = 0;
        from.w = w_;
        from.h = h_;
    SDL_Rect to;
        to.x = x_;
        to.y = y_;

    SDL_Surface *screen = SDL_GetVideoSurface();
    SDL_BlitSurface(image_, &from, screen, &to);
}



void Enemy::fire()
{
    Engine *engine = Engine::get_instance();
    engine->add_bullet(weapon_, down, x_ + w_ / 2 - 15, y_);
}

