#ifndef BALLS_H
#define BALLS_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>

using namespace std;
using namespace sf;
class Balls
{
    private:
    //Değişkenler
    CircleShape shape;
    Vector2f velocity;
    float friction;
    int ballnumber;
    //Fonksiyonlar
    void initBalls(float x, float y, sf::Color color, int ballnumber);
    void initvariable();
    void updateMovement();   
    void updateFriction();  
    void updateCollision();

    public:
    //Yapıcı && Yıkıcı
        Balls(float x, float y, sf::Color color, int ballnumber);
        virtual ~Balls();

    //Fobksiyonlar
    void updateBalls();
    void renderBalls(RenderWindow &target);

};


#endif