////////////////////////////////////////////////////////////////////////////////
//------------------------------------Hero.h----------------------------------//
//                                                                            //
// The hero.                                                                  //
//                                                                            //
// Created by: Rico Roberto Zu�iga                                            //
// Last updated on: January 02, 2003                                          //
//                                                                            //
//------------------------------------Notes-----------------------------------//
//                                                                            //
//------------------------------------ToDo------------------------------------//
//                                                                            //
// * Implement left/right movement animation                                  //
// * Handle firing of weapon, delay like that of the hero                     //
// * Handle collision with enemy, has delay                                   //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


#ifndef HERO_H
#define HERO_H

#include "SDL.h"
#include "Constants.h"
#include "Vehicle.h"

class Hero : public Vehicle
{
public:
    Hero(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames);
    ~Hero();


    void draw();
    void fire();

    void move_left();
    void move_right();
    void move_up();
    void move_down();
        
    //re-initialize values
    void spawn()        { hit_points_ = 20; alive_ = true; this->immortalize(); }
    bool immortalize()  { immortal_ = true; }

private:
    bool immortal_;

};

#endif //HERO_H
