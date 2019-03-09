#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

static int const SCREEN_WIDTH = 640;
static int const SCREEN_HEIGHT = 480;

enum Direction      {left, right, down, up};
enum Weapon_type    {normal, multi};
enum Expl_type      {big, tiny}; //explosion type
enum Enemy_type     {white};
#endif //CONSTANTS_H
