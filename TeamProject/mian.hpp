//
//  mian.hpp
//  TeamProject
//
//  Created by Neil on 11/12/22.
//

#ifndef mian_hpp
#define mian_hpp

#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "yspng.h"
using namespace std;

enum game_states {
    WELCOME_PAGE,
    PLAY,
    PLAYER_DIED,
    GAME_END
};

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

void DrawWelcome();
void DrawBackground();
void DrawEnd();
void DrawPlayerDied();

#endif /* mian_hpp */
