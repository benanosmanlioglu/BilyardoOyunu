#include "Game.h"
//#include "Balls.h"

//Private Fonksiyonlar
void Game::initVariables()
{
    this->Window=nullptr;

}
void Game::initWindow()
{
    this->videoMode.height=500;
    this->videoMode.width=1200;
    this->Window = new sf::RenderWindow (this->videoMode, "Bilyardo Oyunu", sf::Style::Default);
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




//Yapıcı && Yıkıcı
Game::Game()
{
    this->initVariables();
    this->initWindow();
    

    

}
Game::~Game()
{
   delete this-> Window;
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
  
}

void Game::render()
{
    this->Window->clear();

    //Draw objects

    this->Window->display();
}
