#include <iostream>
#include "Game.h"





// Hareket ve özellikler için bir sınıf

int main() 
{   
     //oyun motorum
    Game game;

   

    while (game.running())
     {





        
        game.update();

        game.render();
    }



    return 0;
}