#ifndef BALLS_H
#define BALLS_H
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <cmath>


/*
Toplar ve Fiziki işlemler bu sınıfta
*/
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

    Texture texture;
    Sprite sprite;
    

    //Fonksiyonlar
    void initBalls(float x, float y,  int ballnumber);
    void initvariable();
    void initTextures();
    void initSprite();
    void updateMovement();   
    void updateFriction();  
    void updateCollision();
    float getDistance(Balls* other);
    void separateBalls(Balls* other, float overlap);
    void applyCollisionPhysics(Balls* other);
    
    


    public:
    //Yapıcı && Yıkıcı
        Balls(float x, float y, int ballnumber);
        virtual ~Balls();

    //Fobksiyonlar
    const CircleShape& getShape() const ;
    const Vector2f getVelocity() const ;
    void setVelocity(Vector2f newVelocity);
    void checkAndResolveCollision(Balls* other);
    void updateBalls();
    void renderBalls(RenderWindow &target);

};


#endif