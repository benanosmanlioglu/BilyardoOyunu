#include "Balls.h"

using namespace std;

//Private Fonksiyonlar
void Balls::initBalls(float x, float y, int ballnumber)
{
    this->ballnumber = ballnumber;
    float radius = 25.f;
    this->shape.setRadius(radius);
    this->shape.setPointCount(100); 
    this->shape.setPosition(x, y);
    this->shape.setOrigin(radius, radius);
    
}
void Balls::initTextures()
{
   string path = "bil_top/" + to_string(ballnumber) + ".png";
    this->texture.loadFromFile(path);
        
    
}   
void Balls::initSprite()
{
   this->sprite.setTexture(this->texture);

    sf::FloatRect bounds = this->sprite.getLocalBounds();

    
    float targetSize = 50.f; 

     
    float scaleX = targetSize / bounds.width;
    float scaleY = targetSize / bounds.height;

    this->sprite.setScale(scaleX, scaleY);

    
    this->sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

   

}

float Balls::getDistance(Balls* other)
{
    Vector2f diff = this->shape.getPosition() - other->shape.getPosition();
    return sqrt(diff.x * diff.x + diff.y * diff.y);
}

void Balls::separateBalls(Balls* other, float overlap)
{
    Vector2f relativePos = other->shape.getPosition() - this->shape.getPosition();
    float distance = sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
    
    sf::Vector2f collisionNormal = relativePos / distance;
    
    
    this->shape.move(collisionNormal * -overlap * 0.5f);
    other->shape.move(collisionNormal * overlap * 0.5f);
}

void Balls::applyCollisionPhysics(Balls* other) {
    sf::Vector2f relativePos = other->shape.getPosition() - this->shape.getPosition();
    float distance = std::sqrt(relativePos.x * relativePos.x + relativePos.y * relativePos.y);
    sf::Vector2f n = relativePos / distance; // Normal Vektör

    
    sf::Vector2f relVel = this->velocity - other->velocity;

    
    float vDotN = relVel.x * n.x + relVel.y * n.y;

    
    if (vDotN <= 0) return;

    
    sf::Vector2f impulse = n * vDotN;

    this->velocity -= impulse;
    other->velocity += impulse;
}

void Balls::checkAndResolveCollision(Balls* other) {
    float distance = this->getDistance(other);
    float minDistance = this->shape.getRadius() + other->shape.getRadius();

    if (distance < minDistance) {
        // 1. Önce birbirlerinden ayır
        this->separateBalls(other, minDistance - distance);
        // 2. Sonra fizik yasalarını uygula
        this->applyCollisionPhysics(other);
    }
}



void Balls::initvariable(){
   this->velocity = Vector2f(0.f, 0.f);
   this->friction = 0.99f;
}

void Balls::setVelocity(Vector2f newVelocity)
{
   this->velocity = newVelocity;
   
}

//Yapıcı && Yıkıcı
Balls::Balls(float x, float y,  int ballnumber)
{
   this->initBalls(  x,  y, ballnumber);
   this->initvariable();
   this->initTextures();
   this->initSprite();
   
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
      float offset = 82.f;

      if (pos.x - ballradius < 150.f + offset) 
      { // Hız Sağa Doğru
        this->velocity.x = std::fabs(this->velocity.x); 
        this->shape.setPosition(150.f + offset + ballradius, pos.y);
      }
    
    else if (pos.x + ballradius > 1650.f - offset) 
    {   //HIz Sola Doğru
        this->velocity.x = -std::fabs(this->velocity.x); 
        this->shape.setPosition(1569.f - ballradius, pos.y);
    }

    
    if (pos.y - ballradius < 120.f + offset) 
    {   //HIz Aşağı Doğru
        this->velocity.y = std::fabs(this->velocity.y); 
        this->shape.setPosition(pos.x, 120.f + offset + ballradius);
    }
    
    else if (pos.y + ballradius > 870.f - offset) 
    {   //HIz Yukarı Doğru
        this->velocity.y = -std::fabs(this->velocity.y); 
        this->shape.setPosition(pos.x, 790.f - ballradius);
    }
  }
   
  
  const CircleShape & Balls::getShape() const
   { 
    return this->shape; 
   }
   const Vector2f Balls::getVelocity() const 
   {
     return this->velocity; 
   }
  

 void Balls::updateBalls()
 {
    this->updateMovement();    
    this->updateFriction();  
    this->updateCollision();
   
    this->sprite.setPosition(this->shape.getPosition());
 }
 void Balls::renderBalls(RenderWindow &target)
 {
    target.draw(this->sprite);
    

    
 }