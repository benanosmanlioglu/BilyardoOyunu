#include "Cue.h"
#include <SFML/Graphics.hpp>

//Private Fonksiyonlar
void Cue::initCue()
{

}
void Cue::initVariable()
{ 
     power = 0.f;        
     maxPower = 450.f;   
     isAiming = false;
     impactForce=0.f;
    

}
 void Cue::initTextures()
 {
    if (!this->texture.loadFromFile("cue.png")) 
    {
        std::cout << "HATA: cue.png bulunamadi!" << std::endl;
    }
 }
 void Cue::initSprite()
 {
   this->sprite.setTexture(this->texture);
    
   this->sprite.setScale(0.20f, 0.15f);

    
   FloatRect bounds = this->sprite.getLocalBounds();

   this->sprite.setOrigin(bounds.width / 4.2, -150.f);

 }

 void Cue::updatePosition(Vector2f whiteBallPos)
 {  
   float baseOffset = -150.f;
   
   if (this->isAiming) 
    {
        
        if (this->power < this->maxPower) {
            this->power += 3.8f; 
        }
        this->impactForce = this->power;
    }

    this->sprite.setPosition(whiteBallPos);
    FloatRect bounds = this->sprite.getLocalBounds();

    float driftCorrection = this->power * 0.5f;

    this->sprite.setOrigin(bounds.width / 4.2f - driftCorrection, baseOffset - this->power);

    
   
 }

 void Cue::updatePositionForward()
 {
     if (!this->isAiming && this->power > 0.f) 
   {
    // Istaka topa doğru çok hızlı gitsin (vuruş hızı)
    this->power -= 20.f; 

    // Istaka topa değdiği an (veya çok yaklaştığında)
    if (this->power <= 0.f) 
    {
        this->power = 0.f;
        // İŞTE BURADA VURUŞ GERÇEKLEŞECEK
    }
  }
 }


 void Cue::updateRotation(Vector2f whiteBallPos,Vector2f  mousePos)
 {    
      float dx = mousePos.x - whiteBallPos.x;
      float dy = mousePos.y - whiteBallPos.y;

    //  dereceye çevirme
    float angle = atan2(dy, dx) * 180 / 3.14159265f;

    
    this->sprite.setRotation(angle + 120.f);
 }

//Yapıcı && Yıkıcı
Cue::Cue()
{  
    this->initVariable();
    this->initTextures();
    this->initSprite();
    
}
Cue::~Cue()
{

}

//Fonksiyonlar
void Cue::startAiming() 
{ 
   this->isAiming = true; 
}
void Cue::stopAiming() 
{ 
   this->isAiming = false; 
}
 void Cue::resetPower() 
{ 
  this->power = 0;
}

const float Cue::getPower() const 
{ 
   return this->power; 
}
const float Cue::getimpectPower() const
{
    return this->impactForce;
}
const bool Cue::getAiming() const 
{ 
   return this->isAiming; 
}
float Cue::getRotation() const 
{ 
   return this->sprite.getRotation(); 
}

void Cue::update(Vector2f whiteBallPos, Vector2f mousePos)
{
   this->updatePosition( whiteBallPos);
   this->updateRotation( whiteBallPos, mousePos);
  
}
void Cue::render(RenderWindow &target)
{
   target.draw(this->sprite);
}
