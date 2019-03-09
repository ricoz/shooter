#include "Sprite.h"

Sprite::Sprite(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames)
: image_(image),
  w_(w),
  h_(h),
  x_(x),
  y_(y),
  x_velocity_(x_velocity),
  y_velocity_(y_velocity),
  interval_(interval),
  total_frames_(total_frames),

  frame_(0),
  animating_(1),
  last_update_(SDL_GetTicks())
{
    rect_.x = x_;
    rect_.y = y_;
    rect_.w = w_;
    rect_.h = h_;
}



void Sprite::draw()
{
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


/*
SDL_Surface* Sprite::load_image(char *file)
{
    SDL_Surface *temp1, *temp2;
    temp1 = SDL_LoadBMP(file);
    temp2 = SDL_DisplayFormat(temp1);
    SDL_FreeSurface(temp1);

    return temp2;
}



void Sprite::set_color_key(int r, int g, int b)
{
    SDL_SetColorKey(image_, SDL_SRCCOLORKEY, SDL_MapRGB(image_->format, r, g, b));
}
*/
