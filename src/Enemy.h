////////////////////////////////////////////////////////////////////////////////
//-----------------------------------Enemy.h----------------------------------//
//                                                                            //
// A generic enemy.                                                           //
//                                                                            //
// Created by: Rico Roberto Zuñiga                                            //
// Last updated on: January 02, 2003                                          //
//                                                                            //
//------------------------------------Notes-----------------------------------//
//                                                                            //
//------------------------------------ToDo------------------------------------//
//                                                                            //
// * Implement left/right movement animation                                  //
// * AI : fires at hero when hero is spotted.                                 //
// * Handle enemy type - in the game engine                                   //
// * Handle firing of weapon, delay like that of the hero                     //
// * Handle different enemy animations - in the game engine or in children    //
// * Handle collision with hero, has delay                                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef ENEMY_H
#define ENEMY_H

#include "SDL.h"
#include "Constants.h"
#include "Vehicle.h"

class Enemy : public Vehicle
{
public:
    Enemy(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames);
    ~Enemy();

    void draw();
    void fire();

};

#endif //ENEMY_H
