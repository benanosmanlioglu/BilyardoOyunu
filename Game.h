#ifndef GAME_H
#define GAME_H

#include "Table.h"

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
    Table *table;

    //FOnksiyonlar
    void initVariables();
    void initWindow();
    void pollEvents();
    void initTable();
    

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