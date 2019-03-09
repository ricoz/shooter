////////////////////////////////////////////////////////////////////////////////
//----------------------------------Sprite.h----------------------------------//
//                                                                            //
// A small generic sprite class.                                              //
// Handles animation, movement, and drawing of the objects in the game.       //
//                                                                            //
// Created by: Rico Roberto Zu�iga                                            //
// Created on: December 22, 2003                                              //
//                                                                            //
//------------------------------------Notes-----------------------------------//
//                                                                            //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef SPRITE_H
#define SPRITE_H

#include "SDL.h"
#include "Constants.h"

#include "bitmask/bitmask.h"

class Sprite
{
public:
    Sprite()
    {}
    Sprite(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames);

    virtual ~Sprite()
    {}


    virtual void draw();

    virtual void move_left()            { rect_.x = x_ -= x_velocity_; }
    virtual void move_right()           { rect_.x = x_ += x_velocity_; }
    virtual void move_up()              { rect_.y = y_ -= y_velocity_; }
    virtual void move_down()            { rect_.y = y_ += y_velocity_; }

//  void set_image(SDL_Surface *image)  { image_ = image;                  }
//  void set_image(char *file)          { image_ = this->load_image(file); }
//  void set_color_key(int r, int g, int b);

//  SDL_Surface* load_image(char *file);

    void offset_x(int offset)           { rect_.x = x_ += offset; }
    void offset_y(int offset)           { rect_.y = y_ += offset; }
    void set_x(int x)                   { rect_.x = x_ = x;       }
    void set_y(int y)                   { rect_.y = y_ = y;       }
    void set_xy(int x, int y)           { rect_.x = x_ = x; rect_.y = y_ = y; }

    int  get_x()                        { return x_; }
    int  get_y()                        { return y_; }
    int  get_w()                        { return w_; }
    int  get_h()                        { return h_; }

    void toggle_animation()             { animating_ = !animating_; }
    void start_animation()              { animating_ = 1;           }
    void stop_animation()               { animating_ = 0;           }
    void rewind()                       { frame_     = 0;           }

    SDL_Rect *get_rect()                { return &rect_;            }

protected:
    SDL_Surface  *image_;
    SDL_Rect      rect_;

    int   w_;
    int   h_;
    int   x_;
    int   y_;
    int   x_velocity_;
    int   y_velocity_;

    int   frame_;
    int   total_frames_;

    int   animating_;
    float interval_;
    long  last_update_;

};

#endif //SPRITE_H
