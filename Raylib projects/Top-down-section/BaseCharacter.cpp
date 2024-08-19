#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldPos = worldPosLastFrame;
}

 
 Rectangle BaseCharacter::getCollisionRec()
 {
     return Rectangle{
         getScreenPos().x,
         getScreenPos().y,
         width * scale,
         height * scale
     };
 }

 void BaseCharacter::tick(float deltaTime)
{
    if(!getAlive()) return;
    worldPosLastFrame = worldPos;
    
    //update animation frame
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames)
            frame = 0;
    }

     if (Vector2Length(velocity) != 0.0) // BASICALLY IF DIRECTION IS 0 WE DON'T NEED TO MOVE ANYWHERE
    {

        // set WorldPos = WorldPos + direction
        // vecto2normalize() this will normalize a vector so we don't move faster if we move in a diagonal as opposed to left or right
        // direction vector is normalized, scaled by speed then added to world pos effectively applying the movement.
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed)); // we are scaling our normalize vector by speed. since speed is 4.0 we move 4X faster

        // We can use the turnary operator to write a single line of code in the if and else case in one line.  It's the only operator that works on 3 arguments hence name turnary.
        velocity.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f; //This line is the same as a single line if else statement
        texture = run;
    }
    else
    {
        texture = idle; // If we are not moving i.e vector magnitude = 0 run the idle animation.
    }
    velocity = {}; // zeroing out the velocity makingit effectively 0 after the if else

    //draw the character
    Rectangle source{frame * width, 0.f, rightLeft * width, height}; // source starts drawing texture to middle of screen
    Rectangle dest{getScreenPos().x, getScreenPos().y, scale * width, scale * height};

    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE); 
}

 