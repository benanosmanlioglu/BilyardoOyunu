#ifndef GAME_H
#define GAME_H
#include "Balls.h"
#include "Table.h"
#include "Cue.h"

using namespace sf;
/*
OYUNunu TEMEL İŞLEVLERİ bu sınıfta
-Delik Algılama Sistemi
-Puanlama
-oyun kurallarına bağlı olarak kazanma dorumu göstergesi
-Güç barı
-Boşluğa giren top sayacı

*/

class Game
{   
    private:

    //Değişkenler
     float holeRadius;
     vector<Vector2f> holePositions;
     Font font; 
     Text scoreText;
     Text gameOverText;
     int score;
     bool endgame;
     bool wongame;
     RectangleShape restartButton;
     Text buttonText;
     Text winText;
     int pottedBallCount;
     Text pottedText;
     RectangleShape powerBarOutline;
     RectangleShape powerBarInner;
    
    //Window
    RenderWindow *Window;
    VideoMode videoMode;
    Event event;

    //Oyun Objeleri
    Table *table;
    vector<Balls*> balls;
    Cue *cue;

    //FOnksiyonlar
    void initVariables();
    void initWindow();
    void pollEvents();
    void resetGame();
    void initTable();
    void initAllBalls();
    void initCue();
    void updateCue();
    void updateCueHit();
    bool allBallsStopped();
    void hitWhiteBall();
    void updateBalls();
    void updateBallshape();
    void updateBallColl();
    void updateCollision();
    void initFont();
    void initText();
    bool isWin();
    void updatePowerBar();
    // Boşluk Fonksiyonları
    void initHoles();
    void updateHoles();
    void removeBall(int i);
    void resetWhiteBall();
    

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