#include "Game.h"
#include "Balls.h"
#include "Table.h"

//Private Fonksiyonlar
void Game::initVariables()
{
    this->Window=nullptr;

}
void Game::initWindow()
{
    this->videoMode.height=900;
    this->videoMode.width=1800;
    this->Window = new sf::RenderWindow (this->videoMode, "Bilyardo Oyunu",  sf::Style::Titlebar | sf::Style::Close);
    this->Window->setFramerateLimit(60);
}
void Game::pollEvents()
{ 
while (this->Window->pollEvent(this->event))
  {
    switch (this->event.type)
    {
    case Event::Closed:
        this->Window->close();
        
        break;
    case Event::KeyPressed:
        if (this->event.key.code == Keyboard::Escape)
            this->Window->close();
        break;
           
    default:
        break;
    }
  }

}
void Game::initTable()
{
    this->table = new Table();
}

 void Game::initAllBalls()
 { //Beyaz Top
    this->balls.push_back(new Balls(450.f, 495.f, 0));
   
   
    
    float startX = 1200.f; 
    float startY = 495.f;
    float ballRadius = 25.f;
    int ballNum = 0;

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < i; j++)
        {
            float posx = startX + (i * ballRadius * 1.73f);
            float posy = startY + (j * ballRadius * 2.f) - (i * ballRadius);
             
           
             int currentNumber;

           if (i == 3 && j == 1) 
          {
         
          currentNumber = 8;
          } 
         else 
         {
    
          
             if (ballNum  == 7) 
              {
                 ballNum++; 
              }
               currentNumber = ballNum + 1;
               ballNum++;              
                  
         }

        this->balls.push_back(new Balls(posx, posy, currentNumber));
    }
    
    
 }

}
//Yapıcı && Yıkıcı
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTable();
    this->initAllBalls();
}
Game::~Game()
{
   delete this-> Window;
   delete this-> table;

   for (auto* ball : this->balls)
    {
        delete ball; 
    }
}   


//Accessors (erişim)
const bool Game::running() const
{
    return this->Window->isOpen();
}

//Fonksiyonlar
void Game::update()
{
  this->pollEvents();
 //Topları güncelliyor
  for (auto* ball : this->balls)
{
    ball->updateBalls(); 
}
  
}

void Game::render()
{
    this->Window->clear(Color(30, 30, 30));

    //çizim işlemleri
    this->table->render(*this->Window);

   //Topları çiziyor
   for (auto* ball : this->balls)
   {
    ball->renderBalls(*this->Window);
   }
    
    this->Window->display();

 
}
