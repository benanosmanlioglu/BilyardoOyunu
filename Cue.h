#ifndef CUE_H
#define CUE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using namespace sf;

class Cue
{
    private:
    //Değişkenler
    Texture texture;
    Sprite sprite;
    
    float power = 0.f;        
    float maxPower = 450.f;   
    bool isAiming = false;
    float impactForce=0.f;
    

    //Fonksiyonlar
    void initCue();
    void initTextures();
    void initSprite();
    void initVariable();
    void updatePosition(Vector2f whiteBallPos);
    void updateRotation(Vector2f whiteBallPos,Vector2f  mousePos);
   
    public:
    //Yapıcı && Yıkıcı
    Cue();
    ~Cue();

    //Fonksiyonlar
    void startAiming(); 
    void stopAiming(); 
    void resetPower(); 

    const float getPower() const ;
    const bool getAiming() const ;
    float getRotation() const ;
    const float getimpectPower() const;
     void updatePositionForward();
     

    void update(Vector2f whiteBallPos, Vector2f mousePos);
    void render(RenderWindow &target);
};






#endif