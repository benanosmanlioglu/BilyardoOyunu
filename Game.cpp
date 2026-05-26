#include "Game.h"



//Private Fonksiyonlar
void Game::initVariables()
{
    this->Window = nullptr;
    this->score = 0;
    this->endgame = false;
    this->wongame = false;
    this->pottedBallCount = 0;
    

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
    Vector2i mousePosInt;
    Vector2f mousePos;

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
        mousePosInt = Mouse::getPosition(*this->Window);
        mousePos = this->Window->mapPixelToCoords(mousePosInt);

        
        if (this->restartButton.getGlobalBounds().contains(mousePos))
        {
          this->resetGame();  
        }

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
void Game::resetGame()
{ 
    this->score = 0;
    
    this->endgame = false;

    for (auto* ball : this->balls) {
        delete ball;
    }
    this->balls.clear();

    this->initAllBalls();
    
    this->balls[0]->setVelocity(sf::Vector2f(0.f, 0.f));
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
void Game::initFont()
{
   this->font.loadFromFile("Fonts/arial.ttf");

}
void Game::initText()
{    //Skor
    this->scoreText.setFont(this->font);
    this->scoreText.setCharacterSize(24);
    this->scoreText.setFillColor(sf::Color::White);
    this->scoreText.setPosition(20.f, 20.f);

    // Oyun Bitti!
    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(80);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER!");
    this->gameOverText.setPosition(
        this->videoMode.width / 2.f - 200.f, 
        this->videoMode.height / 2.f - 50.f);

    //Oyunu Tekrarla
    this->restartButton.setSize(Vector2f(200.f, 60.f)); 
    this->restartButton.setFillColor(Color(100, 100, 100, 150)); 
    this->restartButton.setPosition(1620.f, 20.f);
    
    this->buttonText.setFont(this->font);
    this->buttonText.setString("RESTART");
    this->buttonText.setCharacterSize(25);
    this->buttonText.setFillColor(sf::Color::White);

    this->buttonText.setPosition(1645.f, 32.f); 

    //Kazandın
    this->winText.setFont(this->font);
    this->winText.setCharacterSize(80);
    this->winText.setFillColor(Color::Green); 
    this->winText.setString("YOU WIN!\nAll Balls Potted!");

    this->winText.setPosition(
        this->videoMode.width / 2.f - 250.f, 
        this->videoMode.height / 2.f - 50.f
    );

    //Boşluğa Giren Top sayısı
    this->pottedText.setFont(this->font);
    this->pottedText.setCharacterSize(24);
    this->pottedText.setFillColor(sf::Color::Cyan);
    this->pottedText.setPosition(20.f, 60.f);
    this->pottedText.setString("Pot Edilen: 0");

    //Güç Barı
    this->powerBarOutline.setSize(sf::Vector2f(30.f, 200.f));
    this->powerBarOutline.setFillColor(sf::Color::Transparent);
    this->powerBarOutline.setOutlineThickness(2.f);
    this->powerBarOutline.setOutlineColor(sf::Color::White);
    this->powerBarOutline.setPosition(50.f, 350.f);

    this->powerBarInner.setFillColor(sf::Color::Yellow);
    this->powerBarInner.setPosition(50.f, 550.f);
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
bool Game::isWin()
{
    if (endgame==false && wongame==false)
    {
        return true;
    }
    else
    {
        return false;
    }
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
                if (this->balls[i]->getBallNumber() == 8)
                {
                    if (this->balls.size() > 2)
                    {
                      this->gameOverText.setString("GAME OVER!\nEarly 8-Ball!");
                      this->endgame = true; 

                    }
                    else
                    {
                       this->wongame = true; 
                    }

                    this->removeBall(i);
                } 
                else if (i == 0) 
                {   
                    this->score -= 7;
                    this->resetWhiteBall(); 

                    if(this->score < 0)
                    {
                         this->endgame = true;
                    }
                } 
                else 
                {   
                    this->pottedBallCount++; 
                    this->score += 10;
                    this->removeBall(i);    

                    if (this->balls.size() == 1) 
                     {
                       this->endgame = true; 
                     }
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
void Game::updatePowerBar()
{  
     if (this->allBallsStopped() && this->isWin())
    {
        float currentPower = this->cue->getimpectPower();
        float maxPower = 450.f;

        float powerHeight = (currentPower / maxPower) * 200.f;
        this->powerBarInner.setSize(sf::Vector2f(30.f, -powerHeight));
        this->powerBarInner.setPosition(50.f, 550.f);

        if (currentPower > maxPower * 0.70f)
            this->powerBarInner.setFillColor(sf::Color::Red);
        else if (currentPower > maxPower * 0.40f)
             this->powerBarInner.setFillColor(sf::Color(255, 165, 0));
        else  
             this->powerBarInner.setFillColor(sf::Color::Yellow);      
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
    this->initFont();
    this->initText();
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
{ 
    int a=0;

     this->pollEvents();

  if(this->isWin())
  {
    
     //Topları güncelliyor
 
     this->updateBalls();
     this->scoreText.setString("Score: " + to_string(this->score));
     this->pottedText.setString("Pot Edilen: " + std::to_string(this->pottedBallCount));
    // ıstaka güncelleniyor
    if(allBallsStopped())
    {  this->updateCue();
       this->updatePowerBar(); 

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
     this->Window->draw(this->powerBarOutline);
     this->Window->draw(this->powerBarInner);
    }
    //Skore
    this->Window->draw(this->scoreText);
    this->Window->draw(this->pottedText);
    //Tekrar
    this->Window->draw(this->restartButton);
    this->Window->draw(this->buttonText);
    this->Window->draw(this->scoreText);
    
    //Bitirme
    if (this->endgame)
    {  
    
       this->Window->draw(this->gameOverText);   
        
    }

    if(this->wongame)
    {
        this->Window->draw(this->winText); 
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