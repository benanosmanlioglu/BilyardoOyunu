#ifndef Table_H
#define Table_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>



using namespace sf;



class Table
{
    private:

    Texture texture;
    Sprite sprite;

    //FOnksiyonlar
    void initTextures();
    void initSprite();

    
    
    public:

    //Yapıcı && Yıkıcı
        Table();
        virtual ~Table();
    
    //Fonksiyonlar
   
    void update();

    void render(sf::RenderWindow &target);
    
};


#endif