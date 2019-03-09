#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "Sprite.h"
#include "Hero.h"
#include "Constants.h"

class Game
{
public:
    Game();
    ~Game();

    void draw();
    void handle_keyboard();

    SDL_Surface * load_image(char *file);
    void color_key(SDL_Surface *surface, int r, int g, int b);

    void intro();
    bool intro_;
private:
    SDL_Surface *plane;

    Hero *hero_;

    int firing_;
};

#endif //GAME_H
