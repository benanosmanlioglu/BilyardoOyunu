#ifndef GAME_H
#define GAME_H
#include "Balls.h"
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
    vector<Balls*> balls;

    //FOnksiyonlar
    void initVariables();
    void initWindow();
    void pollEvents();
    void initTable();
    void initAllBalls();
    

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