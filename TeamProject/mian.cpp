//
//  mian.cpp
//  TeamProject
//
//  Created by Neil on 11/12/22.
//

#include "mian.hpp"

int main() {
    game_states gameStates = WELCOME_PAGE;
    
    FsOpenWindow(300,300,WINDOWWIDTH,WINDOWHEIGHT,1);
    auto key=FsInkey();
    while(1) {
        FsPollDevice();
        key=FsInkey();
        
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
        
        if (key == FSKEY_ESC) {
           
            break;
        } else if ((gameStates == WELCOME_PAGE || gameStates == PLAYER_DIED) && key == FSKEY_S) {
            DrawWelcome();
            gameStates = PLAY;
        } else if ((gameStates == WELCOME_PAGE || gameStates == PLAYER_DIED) && key == FSKEY_E) {
            DrawEnd();
            gameStates = GAME_END;
            break;
        }
        auto passed=FsPassedTime();
        
        if(gameStates == PLAYER_DIED) {
            DrawPlayerDied();
        }
       
        FsSwapBuffers();
        FsSleep(25);
    }

    return 0;
}

void DrawWelcome() {
    
}

void DrawPlayerDied() {
    
}

void DrawEnd() {
    
}

void DrawBackground() {
    
}
