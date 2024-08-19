#include <raylib.h>

struct AnimData // Stores information we can use over and over. variables inside this are known as member variables
{
  Rectangle rec;
  Vector2 pos;
  int frame;
  float updateTime; 
  float runningTime;  
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;

}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
      // update running time
      data.runningTime += deltaTime;
      if(data.runningTime >= data.updateTime)
      {
          data.runningTime = 0.0;
          // update animation frame
          data.rec.x = data.frame * data.rec.width;
          data.frame++;
          if (data.frame > maxFrame) 
          {
              data.frame = 0;
          }
      }
      return data;
}

int main(){
  int windowDimensions[2];
  windowDimensions[0] = 512;
  windowDimensions[1] = 380;
    


  //Initalize dapper dash window  
    InitWindow(windowDimensions[0],windowDimensions[1], "Dapper Dasher");
    //accelerationduetogravity(pixels/frame)/frame
   // rectangle dimensions
  const int gravity {1'000};

  // nebula Variables
  Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); // spritesheet is 8X8 so a single sprite is the entire sprite sheet divided by 8 in the x and y
  
  
  const int sizeOfNebulae{10};
  AnimData nebulae[sizeOfNebulae]{};


  for (int i = 0; i < sizeOfNebulae; i++)
  {
  nebulae[i].rec.x = 0.0;
  nebulae[i].rec.y = 0.0;
  nebulae[i].rec.width = nebula.width/8;
  nebulae[i].rec.height = nebula.height/8;
  nebulae[i].pos.y = windowDimensions[1] - nebula.height/8;
  nebulae[i].frame = 0;
  nebulae[i].runningTime = 0.0;
  nebulae[i].updateTime = 0.0;
  nebulae[i].pos.x = windowDimensions[0] + i * 300;

  }

  float finishLine{ nebulae[sizeOfNebulae - 1].pos.x };

  // nebula X velocity (pixels per second)
  int nebVel {-200};

// Scarfy Variables
  Texture2D scarfy = LoadTexture("textures/scarfy.png"); // This is a compound data type. It has its own variables.
  
  AnimData scarfyData;
  scarfyData.rec.width = scarfy.width/6;
  scarfyData.rec.height = scarfy.height;
  scarfyData.rec.x = 0;
  scarfyData.rec.y = 0;
  scarfyData.pos.x = windowDimensions[0]/2 - scarfyData.rec.width/2;
  scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height;
  scarfyData.frame = 0;
  scarfyData.updateTime = 1.0/12.0;
  scarfyData.runningTime = 0.0;


bool isInAir{};

// jump velocity (pixels per second)
const int jumpVel {-600};

int velocity{0};
// are we in the air

Texture2D background = LoadTexture("textures/far-buildings.png");
float bgX{};

Texture2D midground = LoadTexture("textures/back-buildings.png");
float mgX{};

Texture2D foreground = LoadTexture("textures/foreground.png");
float fgX{};
     
    bool collision{};
    SetTargetFPS(60);
    while (!WindowShouldClose()){

      //delta time (time since lsat frame)
      const float dt { GetFrameTime()};

      //start drawing
    BeginDrawing();
    ClearBackground(WHITE);

    bgX -= 20 * dt; // scrolling background
    mgX -= 40 * dt;
    fgX -= 80 * dt;

    //scroll the background
    if(bgX <= -background.width * 2)
    {
      bgX = 0.0; // ressting the x value of the backround as soon as it = background width * 2
    }

    //scroll the midground
    if(mgX <= -midground.width * 2)
    {
      mgX = 0.0; // ressting the x value of the backround as soon as it = background width * 2
    }

    //scroll the foreground
    if(fgX <= -foreground.width * 2)
    {
      fgX  = 0.0; // ressting the x value of the backround as soon as it = background width * 2
    }


    // draw the background
    Vector2 bg1Pos{bgX, 0.0};
    DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);
    Vector2 bg2Pos{bgX + background.width * 2, 0.0};
    DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
    
     // draw the midground
    Vector2 mg1Pos{mgX, 0.0};
    DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);
    Vector2 mg2Pos{mgX + midground.width * 2, 0.0};
    DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

    //draw the foreground
    Vector2 fg1Pos{fgX, 0.0};
    DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);
    Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
    DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);
    
    
    if(isOnGround(scarfyData, windowDimensions[1]))
    {
    velocity = 0;    
    isInAir  = false;
    }
    
    else
    {
      //apply gravity 
    velocity += gravity * dt; // multiply by dt since we update every frame
    isInAir = true;
    }
    
    if(IsKeyPressed(KEY_SPACE) == true &&  !isInAir){
        velocity += jumpVel;
        
    }
    
    for(int i = 0; i < sizeOfNebulae; i++){
      // update the position of each nebula
      nebulae[i].pos.x += nebVel * dt;
    }
    
    //update finish line
    finishLine += nebVel * dt;

for(int i = 0; i < sizeOfNebulae; i++){
nebulae[i] = updateAnimData(nebulae[i], dt, 7);

}
    
    // update scarfy position
   scarfyData.pos.y += velocity * dt; // multiply by dt to give velocity by pixels per frame and give scarfy necessary velocity for framerate independence


    if(!isInAir)
    {
      scarfyData = updateAnimData(scarfyData, dt, 5); // refactored code                 
    }

   
    for(AnimData nebula : nebulae)
    {
        float pad{50};
        Rectangle nebRec{
          nebula.pos.x + pad,
          nebula.pos.y + pad,
          nebula.rec.width - 2*pad,
          nebula.rec.height - 2*pad
        };
        Rectangle scarftRec{
          scarfyData.pos.x,
          scarfyData.pos.y,
          scarfyData.rec.width,
          scarfyData.rec.height
        };
        if (CheckCollisionRecs(nebRec, scarftRec))
        {
            collision = true;
        }
    }
  
  if (collision) 
  {
      // lose the game
      DrawText(" Game Over", windowDimensions[0]/4, windowDimensions[1]/2, 30, WHITE);
  }
  else if (scarfyData.pos.x > finishLine)
  {
     DrawText("You Win", windowDimensions[0]/4, windowDimensions[1]/2, 50, WHITE);
  }
  
  else
  {
    for(int i = 0; i < sizeOfNebulae; i++){

  // Draw Nebula
    DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
  }
    // Draw Scarfy
    DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE); // white due to no scarfy tint

  }

 
    //stop drawing
    EndDrawing();
    }
    
    // time that has passed inbetween each animation frame
  
    
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();

}
