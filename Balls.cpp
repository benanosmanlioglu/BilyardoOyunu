#include "Balls.h"

using namespace std;
//Private Fonksiyonlar
void Balls::initBalls(float x, float y, sf::Color color, int ballnumber)
{
    this->ballnumber = ballnumber;
    this->shape.setRadius(15.f); // Top yarıçapı
    this->shape.setFillColor(color);
    this->shape.setPosition(x, y);
    this->shape.setOrigin(15.f, 15.f);
}
void Balls::initvariable(){
   this->velocity = Vector2f(0.f, 0.f);
   this->friction = 0.98f;
}

//Yapıcı && Yıkıcı
Balls::Balls(float x, float y, sf::Color color, int ballnumber)
{
   this->initBalls(  x,  y,  color,  ballnumber);
   this->initvariable();
}
Balls::~Balls()
{

}


//Fonksiyonlar

  
  void Balls::updateMovement()
   {  //Top Hzlandırma && Yavaşlatma
       this->shape.move(this->velocity);
   }   
  void Balls::updateFriction()
   {
      this->velocity *= this->friction;

      if (fabs(this->velocity.x) < 0.1f && fabs(this->velocity.y) < 0.1f)
    {
        this->velocity = sf::Vector2f(0.f, 0.f);
    }
   }
  void Balls::updateCollision()
   { 
       Vector2f pos = this->shape.getPosition();
      float ballradius = this->shape.getRadius();
      float offset = 40.f;

      if (pos.x - ballradius < 150.f + offset) 
      { // Hız Sağa Doğru
        this->velocity.x = std::fabs(this->velocity.x); 
        this->shape.setPosition(150.f + offset + ballradius, pos.y);
      }
    
    else if (pos.x + ballradius > 1650.f - offset) 
    {   //HIz Sola Doğru
        this->velocity.x = -std::fabs(this->velocity.x); 
        this->shape.setPosition(1610.f - ballradius, pos.y);
    }

    
    if (pos.y - ballradius < 120.f + offset) 
    {   //HIz Aşağı Doğru
        this->velocity.y = std::fabs(this->velocity.y); 
        this->shape.setPosition(pos.x, 120.f + offset + ballradius);
    }
    
    else if (pos.y + ballradius > 870.f - offset) 
    {   //HIz Yukarı Doğru
        this->velocity.y = -std::fabs(this->velocity.y); 
        this->shape.setPosition(pos.x, 830.f - ballradius);
    }
  }
    
  

 void Balls::updateBalls()
 {
    this->updateMovement();   
    this->updateFriction();  
    this->updateCollision();
 }
 void Balls::renderBalls(RenderWindow &target)
 {

 }