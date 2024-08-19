#include "Character.h"
#include "raymath.h"



 Character::Character(int winWidth, int winHeight):
 windowWidth(winWidth),
 windowHeight(winHeight)
 {
     width = texture.width/maxFrames;
     height = texture.height;

 }


Vector2 Character::getScreenPos()
{
    return Vector2{ // return calculated value and return it as results in the constructor
        static_cast<float>(windowWidth) / 2.0f - scale * (0.5f * width / 6.0f), // 6 sprites in sheet so width /6 for one sprite
        static_cast<float>(windowHeight) / 2.0f - scale * (0.5f * height)
    };
}


void Character::tick(float deltaTime)
{
 

   
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
       velocity.y -= 1.0; //up is the negative y direction
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;
        

        //Walking audio
    if (IsKeyPressed(KEY_A))
        PlayMusicStream(GetKnightWalk());   
    if (IsKeyPressed(KEY_D))
        PlayMusicStream(GetKnightWalk());   
    if (IsKeyPressed(KEY_W))
        PlayMusicStream(GetKnightWalk());   
    if (IsKeyPressed(KEY_S))
        PlayMusicStream(GetKnightWalk());   



        if(IsKeyReleased(KEY_A))
            StopMusicStream(GetKnightWalk());
        if(IsKeyReleased(KEY_D))
            StopMusicStream(GetKnightWalk());
        if(IsKeyReleased(KEY_W))
            StopMusicStream(GetKnightWalk());
        if(IsKeyReleased(KEY_S))
            StopMusicStream(GetKnightWalk());
       
      BaseCharacter::tick(deltaTime); // Inherit velocity from base: base character is called after velocity since basae character uses velocity then 0's it out
   
   Vector2 origin{};
   Vector2 offset{};
   float rotation{};
   if(rightLeft > 0.f)  // facing right
   {
      origin = {0.f, weapon.height * scale}; // scaling up weapon so  we multiply by scale
      offset = {35.f, 55.f};
      weaponCollisionRec = {
        getScreenPos().x + offset.x,
        getScreenPos().y + offset.y - weapon.height * scale,
        weapon.width * scale,
        weapon.height * scale
      };
     IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = 35.f: rotation = 0.f;
      
   }
   
   else //facing left
   {
       origin = {weapon.width * scale, weapon.height * scale};
       offset = {25.f, 55.f};
         weaponCollisionRec = {
          getScreenPos().x + offset.x - weapon.width * scale, 
          getScreenPos().y + offset.y - weapon.height * scale,
          weapon.width * scale,
          weapon.height * scale
      };
     IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? rotation = -35.f: rotation = 0.f;
   }
   // draw the sword (scale by right left to let texture flip in x axis)
   Rectangle source{0.f, 0.f, static_cast<float> (weapon.width) * rightLeft,static_cast<float> (weapon.height)};
   Rectangle dest{ getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scale, weapon.height * scale};
   DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

 
}

 void Character::takeDamage(float damage)
   {
       health -= damage;
       if(health <=0.f)
       {
           setAlive(false);
       }
   }

   /*
     DrawRectangleLines(
       weaponCollisionRec.x, 
       weaponCollisionRec.y,
       weaponCollisionRec.width,
       weaponCollisionRec.height,
       RED
   );
   */