#ifndef CUE_H
#define CUE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

/*
Istaka Çizimi ve Mekaniği
Vuruş Yönü
Vuruş Gücü Hesabı
Güç Aktarımı(beyaz topa)
*/

using namespace sf;

class Cue
{
    private:
    //Değişkenler
    Texture texture;
    Sprite sprite;
    
    float power ;        
    float maxPower ;   
    bool isAiming ;
    float impactForce ;
    

    //Fonksiyonlar
    
    void initTextures();
    void initSprite();
    void initVariable();
    void updatePosition(Vector2f whiteBallPos);
    void updateRotation(Vector2f whiteBallPos,Vector2f  mousePos);
   
    public:
    //Yapıcı && Yıkıcı
    Cue();
    ~Cue();

    //Accessors (erişim)
    const float getPower() const ;
    const bool getAiming() const ;
    float getRotation() const ;
    const float getimpectPower() const;

    //Fonksiyonlar
    void startAiming(); 
    void stopAiming(); 
    void resetPower(); 
    void updatePositionForward();
    void update(Vector2f whiteBallPos, Vector2f mousePos);
    void render(RenderWindow &target);
};






#endif