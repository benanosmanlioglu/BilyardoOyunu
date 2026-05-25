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

void Game::updateBallshape()
{
     for (auto* ball : this->balls)
  {
    ball->updateBalls(this-> holePositions,this->  holeRadius); 
  }
}
void Game::updateBallColl()
{
     for (int i = 0; i < this->balls.size(); i++)
    {
        for (int j = i + 1; j < this->balls.size(); j++)
        {
            // i. top ile j. top çarpışıyor mu?
            this->balls[i]->checkAndResolveCollision(this->balls[j]);
        }
    }
}    
void Game::updateHoles()
{   
    this->updateCollision();
    
    for (int i = 0; i < this->balls.size(); )
    {
        bool potted = false;

        for (auto& hole : this->holePositions) 
        {
            if (this->balls[i]->checkIfPotted(hole, this->holeRadius)) 
            {
                
                if (i == 0) 
                {
                    this->resetWhiteBall(); 
                } 
                else 
                {
                    this->removeBall(i);    
                }
                
                potted = true; 
                break;         
            }
        }


        if(!potted)
        {
           i++;
        }



    }
}

void Game::updateBalls()
{  
    
   this->updateBallshape();
   this->updateBallColl();
   this->updateHoles();
}
//Yapıcı && Yıkıcı
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initTable();
    this->initHoles();
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
 
 this->updateBalls();

// ıstaka güncelleniyor
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



// Boşluk fonksiyonları
void Game::initHoles()
{
   this->holeRadius = 35.0f;
   
    float leftBound = 150.f;
    float rightBound = 1610.f;
    float topBound = 120.f;
    float bottomBound = 870.f;
    float offset = 80.f;

    float midX = (leftBound + rightBound) / 2.0f;

    this->holePositions.push_back({leftBound + offset, topBound + offset});   
    this->holePositions.push_back({900.f, topBound + offset});              
    this->holePositions.push_back({rightBound - offset, topBound + offset});

    this->holePositions.push_back({leftBound + offset, bottomBound - offset}); 
    this->holePositions.push_back({900.f, bottomBound - offset});            
    this->holePositions.push_back({rightBound - offset, bottomBound - offset});
}

void Game::removeBall(int i)
{
   delete this->balls[i];

   this->balls.erase(this->balls.begin() + i);
}
void Game::resetWhiteBall()
{
    Vector2f position(450.f, 495.f); 
    Vector2f velocity(0.f, 0.f);

    this->balls[0]->setPosition(position);
    this->balls[0]->setVelocity(velocity);

}



void Game::updateCollision()
{
        for (auto* ball : this->balls)
  {
    ball->updateCollision(this-> holePositions,this->  holeRadius); 
  }
}