#include "Engine.h"

Engine* Engine::get_instance ()
{
    static Engine engine;
    return &engine;
}



Engine::Engine()
: intro_(true),
  firing_(0),
  hero_(0)
{
    srand(time(NULL));
    this->init_SDL();

    bullet_image_           = this->load_image("gfx/bullets.bmp");
    hero_image_             = this->load_image("gfx/plane.bmp");
    enemy_image_            = this->load_image("gfx/enemy.bmp");
    big_explosion_image_    = this->load_image("gfx/big_explosion.bmp");
    small_explosion_image_  = this->load_image("gfx/small_explosion.bmp");
    this->set_color_key(hero_image_,   255, 0, 255);
    this->set_color_key(bullet_image_, 255, 0, 255);
    this->set_color_key(enemy_image_,  255, 0, 255);
    this->set_color_key(big_explosion_image_, 255, 0, 255);
    this->set_color_key(small_explosion_image_, 255, 0, 255);

    enemies_.resize(0);
    hero_bullets_.resize(0);
    explosions_.resize(0);

}



Engine::~Engine()
{
    for(BVI vi = hero_bullets_.begin(); vi != hero_bullets_.end(); vi++) {

        delete *vi;
//      printf("deleting...\n");
    }

    for(EVI vi = explosions_.begin(); vi != explosions_.end(); vi++) {

        delete *vi;
//      printf("deleting...\n");
    }
        
    for(EnVI vi = enemies_.begin(); vi != enemies_.end(); vi++) {

        delete *vi;
//      printf("deleting...\n");
    }

    delete hero_;

//  printf("\nsuccessfully called the destructor...\n");
}



void Engine::init()
{
    this->add_hero();
        
    for(int i = 0; i < 10; i++)
        this->add_enemy(white, i * 64 + 2, -((rand() % 80) + 64));

}



void Engine::add_bullet(Weapon_type type, Direction direction, int x, int y)
{
    //Note to self: check for weapon type...
    //if(type == ) {
    hero_bullets_.push_back(new Bullet(bullet_image_, direction, 32, 32, x, y, 0, 5, 5));
}


void Engine::add_explosion(Expl_type type, int x, int y)
{
    if(type == big) {
        
        explosions_.push_back(new Explosion(big_explosion_image_, 64, 64, x, y, 50, 7));
    } else
    if(type == tiny) {
        
        explosions_.push_back(new Explosion(small_explosion_image_, 32, 32, x, y, 50, 7));
    }
}



void Engine::add_enemy(Enemy_type type, int x, int y)
{
    if(type == white) {

        enemies_.push_back(new Enemy(enemy_image_, 64, 64, x, y, 1, 1, 25, 3));
    }//else
}



void Engine::add_hero()
{
    intro_ = true;

    if(hero_ == 0)
        hero_  = new Hero(hero_image_, 64, 64, SCREEN_WIDTH / 2 - 64 / 2, SCREEN_HEIGHT - 64, 2, 2, 25, 3);
    else {

        hero_->set_x(SCREEN_WIDTH / 2 - 64 / 2);
        hero_->set_y(SCREEN_HEIGHT - 64);
        hero_->spawn();
    }

}



void Engine::update_bullets()
{
    for(BVI vi = hero_bullets_.begin(); vi != hero_bullets_.end(); vi++) {
        
        if((*vi)->alive()) {
        
            for(EnVI evi = enemies_.begin(); evi != enemies_.end(); evi++) {

                if(this->collision(*(*vi), (*vi)->get_bitmask(), *(*evi), (*evi)->get_bitmask())) {
        
                    (*vi)->kill();
                    (*evi)->hit(hero_->get_damage());
                    this->add_explosion(tiny, (*vi)->get_x() + (*vi)->get_w() / 2, (*evi)->get_y() + (*evi)->get_h() - 32 / 2);
                    break;
                    //damage the enemy
                    //when hitpoints are depleted kill and explode
                    //animate a hit explosion
                    //kill the bullet
                }
            }
        }

        if((*vi)->alive()) (*vi)->draw();
        else { delete *vi; hero_bullets_.erase(vi); vi--; }
    }
}



void Engine::update_explosions()
{
    for(EVI vi = explosions_.begin(); vi != explosions_.end(); vi++) {
        
        if((*vi)->alive()) {
        
            (*vi)->draw();
        }
        if(!(*vi)->alive()) {
        
            delete *vi;
            explosions_.erase(vi);
            vi--;
        }
    }
}



void Engine::update_enemies()
{
    if(enemies_.size() < 10) {
        
        for(int i = 0; i < 10 - enemies_.size(); i++) {

            this->add_enemy(white, rand() % (640 - 64), -((rand() % 80) + 64));
        }
    }
        
    for(EnVI vi = enemies_.begin(); vi != enemies_.end(); vi++) {
        
        if((*vi)->alive()) {
        
            if(this->collision(*(*vi), (*vi)->get_bitmask(), *hero_, hero_->get_bitmask())) {
            
//              (*vi)->hit(5);
//              hero_->hit(5);
//              break;
//              this->add_explosion(tiny, (*vi)->get_x() + (*vi)->get_w() / 2, (*evi)->get_y() + (*evi)->get_h() - 32 / 2);
            }

            (*vi)->move_down();
            (*vi)->draw();
        }
        if(!(*vi)->alive()) {
        
            delete *vi;
            enemies_.erase(vi);
            vi--;
        }
    }
        
}



void Engine::update_hero()
{
    if(hero_->alive()) {
        
        hero_->draw();
    }
    else {
        
        //check if there are lives left, decrement or game over
        this->add_hero();
    }

}
void Engine::update()
{
    SDL_Surface *screen = SDL_GetVideoSurface();
        
    //draw background
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 67, 171));

    this->update_bullets();
    this->update_enemies();
    this->update_hero();
    this->update_explosions();

    //update other entities

    //flip the screen
    SDL_Flip(screen);
}



SDL_Surface * Engine::load_image(char *file)
{
    SDL_Surface *temp1, *temp2;
    temp1 = SDL_LoadBMP(file);
    temp2 = SDL_DisplayFormat(temp1);
    SDL_FreeSurface(temp1);

    return temp2;
}



void Engine::set_color_key(SDL_Surface *image, int r, int g, int b)
{
    SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, r, g, b));
}



void Engine::handle_keyboard()
{
    Uint8* keys = SDL_GetKeyState(NULL);


    if ( keys[SDLK_z] && (!firing_ || firing_ == 25) ) {

        hero_->fire();
        if(firing_ == 25) firing_ = 0;
        if(!firing_) firing_ = 1;
    }
    else if( keys[SDLK_z] )     { firing_++;     }
    else if( !keys[SDLK_z] )    { firing_ = 0;   }

    //The spacebar doesn't seem to work
//  if ( keys[SDLK_SPACE] ) { hero_->fire();       }

    if ( keys[SDLK_UP]    ) { hero_->move_up();    }
    if ( keys[SDLK_DOWN]  ) { hero_->move_down();  }
    if ( keys[SDLK_LEFT]  ) { hero_->move_left();  }
    if ( keys[SDLK_RIGHT] ) { hero_->move_right(); }
}



void Engine::intro()
{
    if(!intro_) return;
        
    static int count = 0;
    if(count == 70) {

        count = intro_ = 0;
    }
        
    hero_->move_up();
    this->update();

    count++;
}



void Engine::init_SDL()
{
    if( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
    {
        printf("Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    atexit(SDL_Quit);

    static SDL_Surface *screen;

//  screen=SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    screen=SDL_SetVideoMode(640, 480, 0, SDL_HWSURFACE|SDL_DOUBLEBUF);

    if(screen == NULL)
    {
        printf("Unable to set 640x480 video: %s\n", SDL_GetError());
        exit(1);
    }


}



void Engine::game_loop()
{
    int done = 0;
    SDL_Event event;
        
    this->init();

    while(done == 0)                    {

        while(SDL_PollEvent(&event))    {

            switch(event.type)          {

                case SDL_QUIT:
                    done = 1;
                    break;

                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) { done = 1; }
                    break;

        }}

//      this->intro();  //need to optimize
        this->handle_keyboard();
        this->update();
    }
}


bitmask *Engine::create_bitmask(SDL_Surface *image, SDL_Rect &rect)
{
    if(image == 0) return 0;
        
    if(!(image->flags & SDL_SRCCOLORKEY)) {
        
        printf("Can't create bitmask - no colorkey\n");
        return 0;
    }  

    Uint32 colorkey = image->format->colorkey;
    bitmask *mask = bitmask_create(rect.w, rect.h);
    if(mask == 0) return 0;
        
    SDL_LockSurface(image);
  
    for( int y = 0; y < rect.h; y++)    {

        for(int x = 0; x < rect.w; x++) {

            Uint32 pixel = this->get_pixel(image, x + rect.x, y + rect.y);

            if(pixel == colorkey)       {

                bitmask_clearbit(mask,x,y);
            }

            else                    {

                bitmask_setbit(mask,x,y);
            }
    }}

    SDL_UnlockSurface(image);

    return mask;
}



Uint32 Engine::get_pixel(SDL_Surface *image, int x, int y)
{
    int bpp = image->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)image->pixels + y * image->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}


//add a bounding box check for faster collision detection
bool Engine::collision(Sprite &sprite1, bitmask *mask1, Sprite &sprite2, bitmask *mask2)
{
    SDL_Rect *rect1 = sprite1.get_rect();
    SDL_Rect *rect2 = sprite2.get_rect();

    if(!this->intersect_rect(rect1, rect2)) return false;
        
    int x = rect2->x - rect1->x;
    int y = rect2->y - rect1->y;

    if(bitmask_overlap(mask1 , mask2, x, y)) {

        return true;
    }
    else {

        return false;
    }
}



bool Engine::intersect_rect(SDL_Rect *rect1, SDL_Rect *rect2)
{
    return !(rect1->x > rect2->x + rect2->w || rect2->x > rect1->x + rect1->w ||
        rect1->y > rect2->y + rect2->h || rect2->y > rect1->y + rect1->h);
}
