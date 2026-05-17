#include "Table.h"


//private Fonksiyornlar

void Table::initTextures()
{
   this->texture.loadFromFile("bilyardo_gelismis.jpeg");
  
}
void Table::initSprite()
{
    this->sprite.setTexture(this->texture);


    //boyut ayarlama
    this->sprite.setScale(
        1500.f / this->texture.getSize().x,
        750.f / this->texture.getSize().y
    );

   this->sprite.setPosition(
    (1800.f - 1500.f) / 2.f, 
   120.f
);
}


//Yapıcı && Yıkıcı
Table::Table()
{  
    this->initTextures();
    this->initSprite();
    
}
Table::~Table()
{

}

//Fonksiyonlar

 void Table::update()
 {

 }
 void Table::render(sf::RenderWindow &target)
 {
     target.draw(this->sprite);
}