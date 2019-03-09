#include "Engine.h"

int main(int argc, char *argv[])
{
    Engine *engine = Engine::get_instance();

    engine->game_loop();

    return 0;
}

