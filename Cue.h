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
    

    //Fonksiyonlar
    void initCue();
    void initTextures();
    void initSprite();
    void updatePosition(Vector2f whiteBallPos);
    void updateRotation(Vector2f whiteBallPos,Vector2f  mousePos);
    public:
    //Yapıcı && Yıkıcı
    Cue();
    ~Cue();

    //Fonksiyonlar
     

    void update(Vector2f whiteBallPos, Vector2f mousePos);
    void render(RenderWindow &target);
};






#endif