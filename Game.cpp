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


//Yapıcı && Yıkıcı
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTable();

}
Game::~Game()
{
   delete this-> Window;
   delete this-> table;
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

    //çizim işlemleri
    this->table->render(*this->Window);

    this->Window->display();
}
