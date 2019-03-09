#include "Vehicle.h"
#include "Engine.h"

Vehicle::Vehicle(SDL_Surface *image, int w, int h, int x, int y, int x_velocity, int y_velocity, float interval, int total_frames)
: Sprite(image, w, h, x, y, x_velocity, y_velocity, interval, total_frames),
  alive_(true),
  hit_points_(15),
  damage_(5),
  weapon_(normal)
{
    //don't create a vehicle in the Engine constructor!
    Engine *engine = Engine::get_instance();

    //create the bitmasks
    bitmasks_.resize(0);
    SDL_Rect mask;
        mask.h = h;
        mask.w = w;
        mask.x = 0;
        mask.y = 0;

    for(int i = 0; i < total_frames; i++) {

        mask.x = i * mask.w;
        bitmasks_.push_back(engine->create_bitmask(image, mask));
    }
}



Vehicle::~Vehicle()
{
    //destroy the bitmasks
    for(BMVI vi = bitmasks_.begin(); vi != bitmasks_.end(); vi++) {

        bitmask_free(*vi);  
    }
}



void Vehicle::explode()
{
    Engine *engine = Engine::get_instance();
    engine->add_explosion(big, x_, y_);

}



void Vehicle::hit(int damage)
{
    hit_points_ -= damage;

    if(hit_points_ <= 0) {

        alive_ = false; 
        this->explode();
    }
}
