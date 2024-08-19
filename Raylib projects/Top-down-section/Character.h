#ifndef CHARACTER_H // if symbol is not defined. --> define it then if it gets defined again skip the body and don't include the header to avoid copies
#define CHARACTER_H

#include <raylib.h>
#include "BaseCharacter.h"
class Character : public BaseCharacter
{
public:
    Character( int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;  
    virtual Vector2 getScreenPos() override;
    Rectangle getWeaponCollisionRec() { return weaponCollisionRec;}
    float getHealth() const { return health; }
    void takeDamage(float damage);
    Sound GetKnightSlash() {return KnightSlash;}
    Music GetKnightWalk() {return KnightWalk;}
private:
int windowWidth{};
int windowHeight{};
Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
Rectangle weaponCollisionRec{};
float health{100.f};
Sound KnightSlash = LoadSound("Audio/KnightSlash.ogg");
Music KnightWalk = LoadMusicStream("Audio/KnightWalk.ogg");
   
};
#endif