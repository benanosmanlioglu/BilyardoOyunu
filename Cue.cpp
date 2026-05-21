#include "Cue.h"
#include <SFML/Graphics.hpp>

//Private Fonksiyonlar
void Cue::initCue()
{

}
 void Cue::initTextures()
 {
    if (!this->texture.loadFromFile("cue.png")) {
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
    this->sprite.setPosition(whiteBallPos);
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
{   this->initTextures();
    this->initSprite();
    
}
Cue::~Cue()
{

}

//Fonksiyonlar
void Cue::update(Vector2f whiteBallPos, Vector2f mousePos)
{
   this->updatePosition( whiteBallPos);
   this->updateRotation( whiteBallPos, mousePos);
}
void Cue::render(RenderWindow &target)
{
   target.draw(this->sprite);
}
