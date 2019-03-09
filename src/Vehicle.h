////////////////////////////////////////////////////////////////////////////////
//----------------------------------Vehicle.h---------------------------------//
//                                                                            //
// A superclass defining hero ships, enemy ships, enemy tanks, and other      //
// 'vehicles'.                                                                //
//                                                                            //
// Created by: Rico Roberto Zu�iga                                            //
// Last updated on: January 02, 2003                                          //
//                                                                            //
//------------------------------------Notes-----------------------------------//
//                                                                            //
//------------------------------------ToDo------------------------------------//
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef VEHICLE_H
#define VEHICLE_H

#include "SDL.h"
#include "Constants.h"
#include "Sprite.h"


#include <vector>
#include "bitmask/bitmask.h"

typedef std::vector<bitmask*> Bitmasks;
typedef std::vector<bitmask*>::iterator BMVI;

class Vehicle : public Sprite
{
public:
    Vehicle(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames);
    virtual ~Vehicle();

    virtual void fire() = 0;
    void explode();

    void kill()                                 { alive_ = false;   }
    bool alive()                                { return alive_;    }

    Weapon_type get_weapon_type()               { return weapon_;   }
    void set_weapon_type(Weapon_type weapon)    { weapon_ = weapon; }

    void hit(int damage);
    void set_hit_points(int hit_points)         { hit_points_  = hit_points; }
    void increase_hit_points(int hit_points)    { hit_points_ += hit_points; }

    int  get_damage()                           { return damage_;   }
    void set_damage(int damage)                 { damage_ = damage; }

    bitmask *get_bitmask()                      { return bitmasks_[frame_];  }

protected:
    int  hit_points_;
    int  damage_;
    bool alive_;

    Weapon_type weapon_;
        
    Bitmasks bitmasks_;

private:

};

#endif //VEHICLE_H
