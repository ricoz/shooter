#include "Explosion.h"

void Explosion::draw()
{
    if(animating_ == 1)
    {
        if(last_update_ + interval_ < SDL_GetTicks())
        {
            frame_++;
            // animate once
            if(frame_ > total_frames_ - 1) alive_ = false;
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
