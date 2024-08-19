#ifndef BASE_CHARACTER_H // if this name is not defined then we can include all the code below
#define BASE_CHARACTER_H // defining symbol
#include "raylib.h"

class BaseCharacter{
public:
BaseCharacter();
Vector2 getWorldPos() { return worldPos; }
void undoMovement();
Rectangle getCollisionRec();
virtual void tick(float deltaTime);  
virtual Vector2 getScreenPos() = 0; // Since this is going to be overriden in character and enemy and doesn't need a defininition here it will be a pure virtual function
bool getAlive() { return alive; }
void setAlive(bool isAlive) {alive = isAlive;}
    protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 screenPos{};
    Vector2 worldPos{};
    Vector2 worldPosLastFrame{};
    // 1 :facing right direction, -1 : facing left direction
    float rightLeft{1.f};
    //Animation Variables
    float runningTime{};
    int frame{};
    int maxFrames{6};
    float updateTime{1.f / 12.f};
    float speed{4.f};
    float width{};
    float height{};
    float scale{4.0f};
    Vector2 velocity{};

private:
bool alive{true};

};

#endif // "closing curly brace"