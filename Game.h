#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
/*
OYUNunu TEMEL İŞLEVLERİ bu sınıfta
*/

class Game
{   
    private:
    //Değişkenler

    //Window
    RenderWindow *Window;
    VideoMode videoMode;
    Event event;

    //Oyun Objeleri
    std::vector<CircleShape> balls;

    //FOnksiyonlar
    void initVariables();
    void initWindow();
    void pollEvents();
    

    public:

    //Yapıcı && Yıkıcı
        Game();
        virtual ~Game();
    //Accessors (erişim)
    const bool running() const;   
    
    //Fonksiyonlar
    
    void update();
    void render();    

};

#endif