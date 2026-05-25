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
    bool isPotted;

    Texture texture;
    Sprite sprite;
    

    //Fonksiyonlar
    void initBalls(float x, float y,  int ballnumber);
    void initvariable();
    void initTextures();
    void initSprite();
    void updateMovement();   
    void updateFriction();  
   
    float getDistance(Balls* other);
    void separateBalls(Balls* other, float overlap);
    void applyCollisionPhysics(Balls* other);
    bool isNearHole(const vector<Vector2f>& holePositions, float holeRadius);
    
    
    


    public:
    //Yapıcı && Yıkıcı
        Balls(float x, float y, int ballnumber);
        virtual ~Balls();

    //Fobksiyonlar
    const CircleShape& getShape() const ;
    const Vector2f getVelocity() const ;
    void setVelocity(Vector2f newVelocity);
    void setPosition(Vector2f newPosition);
    void checkAndResolveCollision(Balls* other);
    void updateBalls(const std::vector<sf::Vector2f>& holePositions, float holeRadius);
    void renderBalls(RenderWindow &target);
    bool checkIfPotted(Vector2f holePos, float holeRadius);
    void updateCollision(const vector<Vector2f>& holePositions, float holeRadius);
    bool getIsPotted() const;
   
};


#endif