#include "Hero.h"
#include "Engine.h"

Hero::Hero(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames)
: Vehicle(image, w, h, x, y, x_velocity, y_velocity, interval, total_frames),
  immortal_(true)
{}

Hero::~Hero()
{}
////////////////////////////////////////////////////////////////////////////////
//----------------------------------movement----------------------------------//
//                                                                            //
void Hero::move_left()
{
    if(x_ <= 0)
        return;

    rect_.x = x_ -= x_velocity_;
}

void Hero::move_right()
{
    if(x_ + w_ >= SCREEN_WIDTH)
        return;

    rect_.x = x_ += x_velocity_;
}

void Hero::move_up()
{
    if(y_ <= -6)
        return;

    rect_.y = y_ -= y_velocity_;
}

void Hero::move_down()
{
    if(y_ + h_ >= SCREEN_HEIGHT)
        return;

    rect_.y = y_ += y_velocity_;
}
//                                                                            //
//--------------------------------end movement--------------------------------//
////////////////////////////////////////////////////////////////////////////////



void Hero::draw()
{
    //if(immortal_) then draw a shield, if 3 seconds has elapsed, then make mortal again
    if(animating_ == 1)
    {
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



void Hero::fire()
{
    Engine *engine = Engine::get_instance();
    engine->add_bullet(normal, up, x_ + w_ / 2 - 32 / 2, y_);
}
