#include "Game.h"



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
    case Event::MouseButtonPressed:
        if(this->event.mouseButton.button == Mouse::Left)
        {
            if (this->allBallsStopped()) 
                {
                    this->cue->startAiming();
                }
        }     
        break;
    case Event::MouseButtonReleased:
         if(this->event.mouseButton.button == Mouse::Left)
         {
            if (this->cue->getAiming()) 
                {
                    
                    this->cue->stopAiming();
                    
                }
         }
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

void Game::initCue()
{
    this-> cue = new Cue();
}
bool Game::allBallsStopped()
{
    for (auto* ball : this->balls) 
    {
        // Hız vektörü sıfır değilse bir şeyler hala hareket ediyordur
        if (ball->getVelocity() != sf::Vector2f(0.f, 0.f)) 
        {
            return false;
        }
    }

    return true;
}

void Game::updateCue()
{
    if (this->cue != nullptr)
    {
        Vector2i mousePosInt = Mouse::getPosition(*this->Window);
        Vector2f mousePos = this->Window->mapPixelToCoords(mousePosInt);

        Vector2f whiteBallPos = this->balls[0]->getShape().getPosition();

        this->cue->update(whiteBallPos, mousePos);
    }
    

}

void Game::updateCueHit()
{
  if (!this->cue->getAiming() )
    {
        // Istaka topa tam değmek üzereyken (power 20'den küçükse vuruşu yap)
        if (this->cue->getPower() <= 15.f) 
        {
            this->hitWhiteBall();
            this->cue->resetPower(); 
        }
    }
}

void Game::hitWhiteBall()
{
   float angleRad = (this->cue->getRotation() + 245.f) * 3.14159265f / 180.f;

   float powerScale = 0.10f; 
   float finalPower = this->cue->getimpectPower() * powerScale;

    Vector2f newVelocity;
    newVelocity.x = std::cos(angleRad) * finalPower;
    newVelocity.y = std::sin(angleRad) * finalPower;

    if (!this->balls.empty()) {
        this->balls[0]->setVelocity(newVelocity);
    }
}
//Yapıcı && Yıkıcı
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTable();
    this->initAllBalls();
    this->initCue();
}
Game::~Game()
{
   delete this-> Window;
   delete this-> table;

   for (auto* ball : this-> balls)
    {
        delete ball; 
    }
    
    this->balls.clear();
    delete this-> cue;
}   


//Accessors (erişim)
const bool Game::running() const
{
    return this->Window->isOpen();
}

//Fonksiyonlar
void Game::update()
{ int a=0;
  this->pollEvents();
 //Topları güncelliyor
  for (auto* ball : this->balls)
{
    ball->updateBalls(); 
}
 if(allBallsStopped())
 {  this->updateCue();

    if(this->cue->getPower() > 15.f && !(this->cue->getAiming()))
    {
      this->cue->updatePositionForward();
      a++;
    }
    if(a==1)
    {
       this->updateCueHit();
    }

    
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

    if(allBallsStopped())
    {
     this->cue->render(*this->Window);
    }
    
    this->Window->display();

 
}
