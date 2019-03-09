#include "Game.h"
#include "Engine.h"

Game::Game()
: intro_(true),
  firing_(0)
{
    plane = this->load_image("plane.bmp");
    this->color_key(plane, 255, 0, 255);

    hero_ = new Hero(plane, 64, 64, SCREEN_WIDTH / 2 - 64 / 2, SCREEN_HEIGHT, 2, 2, 25, 3);
}



Game::~Game()
{
    delete hero_;
}



void Game::draw()
{
    SDL_Surface *screen = SDL_GetVideoSurface();
    Engine *engine = Engine::get_instance();

    //draw background
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 67, 171));

    //draw the sprites
    hero_->draw();

    engine->update();

    //flip the screen
    SDL_Flip(screen);
}



void Game::handle_keyboard()
{
    Uint8* keys = SDL_GetKeyState(NULL);


    if ( keys[SDLK_z] && (!firing_ || firing_ == 25) ) {

        hero_->fire();
        if(firing_ == 25) firing_ = 0;
        if(!firing_) firing_ = 1;
    }
    else if( keys[SDLK_z] )     { firing_++;     }
    else if( !keys[SDLK_z] )    { firing_ = 0;   }


//  if ( keys[SDLK_SPACE] ) { hero_->fire();       }
//  if ( keys[SDLK_z] ) { printf("firing...\n"); }

    if ( keys[SDLK_UP]    ) { hero_->move_up();    }
    if ( keys[SDLK_DOWN]  ) { hero_->move_down();  }
    if ( keys[SDLK_LEFT]  ) { hero_->move_left();  }
    if ( keys[SDLK_RIGHT] ) { hero_->move_right(); }
}



SDL_Surface * Game::load_image(char *file)
{
    SDL_Surface *temp1, *temp2;
    temp1 = SDL_LoadBMP(file);
    temp2 = SDL_DisplayFormat(temp1);
    SDL_FreeSurface(temp1);

    return temp2;
}



void Game::color_key(SDL_Surface *surface, int r, int g, int b)
{
    SDL_SetColorKey(surface, SDL_SRCCOLORKEY, SDL_MapRGB(surface->format, r, g, b));
}



void Game::intro()
{
    if(!intro_) return;
    intro_ = false;

    for(int i = 0; i < 70; i++) {

        hero_->move_up();
        this->draw();
    }
}
