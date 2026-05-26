#include <iostream>
#include "Game.h"





// Hareket ve özellikler için bir sınıf

int main() 
{   
     //oyun motoru
    Game game;

   

    while (game.running())
     {





        
        game.update();

        game.render();
    }



    return 0;
}