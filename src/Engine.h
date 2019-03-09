///////////////////////////////////////////////////////////////////////////////////
//------------------------------------Engine.h-----------------------------------//
//                                      v 1.0                                    //
//                                                                               //
// A single threaded game engine that handles the entities in the game.          //
//                                                                               //
// Created by: Rico Roberto Zuñiga                                               //
// Created on: December 27, 2003                                                 //
//                                                                               //
//-------------------------------------Notes-------------------------------------//
//                                                                               //
//                                                                               //
///////////////////////////////////////////////////////////////////////////////////

#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "Constants.h"
#include <vector>
#include <time.h>

#include "bitmask/bitmask.h"

#include "Sprite.h"
#include "Hero.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explosion.h"


//typedef std::vector<Bullet> Bullets;
//typedef std::vector<Bullet>::iterator BVI;
typedef std::vector<Bullet*> Bullets;
typedef std::vector<Bullet*>::iterator BVI;

typedef std::vector<Explosion*> Explosions;
typedef std::vector<Explosion*>::iterator EVI;

typedef std::vector<Enemy*> Enemies;
typedef std::vector<Enemy*>::iterator EnVI;

class Engine
{
public:
    static Engine* get_instance();

    void game_loop();

    void add_bullet(Weapon_type type, Direction direction, int x, int y);
    void add_explosion(Expl_type type, int x, int y);
    void add_enemy(Enemy_type type, int x, int y);
    void add_hero();

    bitmask *create_bitmask(SDL_Surface *image, SDL_Rect &rect);
        
protected:
    Engine();
    ~Engine();

    void init();
    void init_SDL();

    void intro();
    void handle_keyboard();
    void update();

    void update_bullets();
    void update_explosions();
    void update_enemies();
    void update_hero();

    SDL_Surface *load_image(char *file);
    void set_color_key(SDL_Surface *image, int r, int g, int b);
        
    //collision detection
    Uint32 get_pixel(SDL_Surface *image, int x, int y);

    bool    collision(Sprite &sprite1, bitmask *mask1, Sprite &sprite2, bitmask *mask2);
    bool    intersect_rect(SDL_Rect *rect1, SDL_Rect *rect2);
        
private:
    //the images, load only once, reuse often
    SDL_Surface *bullet_image_;
    SDL_Surface *big_explosion_image_;
    SDL_Surface *small_explosion_image_;
    SDL_Surface *hero_image_;
    SDL_Surface *enemy_image_;

    //entities
    Bullets hero_bullets_;
    Explosions explosions_;
    Enemies enemies_;
    Hero *hero_;

    //some useful flags
    bool intro_;
    int  firing_;
};

#endif //ENGINE_H
