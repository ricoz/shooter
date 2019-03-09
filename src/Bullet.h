////////////////////////////////////////////////////////////////////////////////
//----------------------------------Bullet.h----------------------------------//
//                                                                            //
// A generic bullet.                                                          //
//                                                                            //
// Created by: Rico Roberto Zuñiga                                            //
// Last updated on: January 02, 2003                                          //
//                                                                            //
//------------------------------------Notes-----------------------------------//
//                                                                            //
// Different bullet types, and animation types will be handled by the game    //
// engine. The bullet doesn't have a damage property, damage will be based    //
// on the ship's damage effect.                                               //
//                                                                            //
//------------------------------------ToDo------------------------------------//
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "Constants.h"
#include "Sprite.h"
#include "bitmask/bitmask.h"

class Bullet : public Sprite
{
public:
    Bullet()
    {}
    Bullet(SDL_Surface *image, Direction direction, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval);
    ~Bullet()
    {
        bitmask_free(bitmask_);
    }

    void draw();

    bool alive()                { return alive_;    }
    void kill()                 { alive_ = false;   }

    bitmask *get_bitmask()      { return bitmask_;  }

private:
    Direction direction_;   //up or down only
    bool alive_;

    bitmask *bitmask_;

};

#endif //BULLET_H

