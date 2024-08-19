#include <raylib.h>
#include <raymath.h>
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include "string" // using string library


int main()
{

    // Initalize window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 384;
    windowDimensions[1] = 384;

    // Initalize gamewindow
    InitWindow(windowDimensions[0], windowDimensions[1], "Classy Clash");
    InitAudioDevice();

    Music BGM = LoadMusicStream("Audio/8_Bit_Adventure_BGM.mp3");
    SetMasterVolume(1.0f);

    PlayMusicStream(BGM);
    SetMusicVolume(BGM, 0.4f);

    
    Texture2D WorldMap = LoadTexture("nature_tileset/WorldMap.png");
    float WMx{};
    //braced initalization for vector position of world map
    Vector2 WMapPos{WMx, 0.0};
    const float mapScale{4.0f};

    Character knight{windowDimensions[0], windowDimensions[1]};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{Vector2{800.f, 300.f}, LoadTexture("characters/goblin_idle_spritesheet.png"), LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime[5]{
        Enemy{Vector2{200.f, 600.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")},
        Enemy{Vector2{450.f, 550.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")},
        Enemy{Vector2{650.f, 350.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")},
        Enemy{Vector2{100.f, 420.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")},
        Enemy{Vector2{700.f, 300.f}, LoadTexture("characters/slime_idle_spritesheet.png"), LoadTexture("characters/slime_run_spritesheet.png")}

    };
    Enemy *enemies[]{
        &goblin,
        &slime[0],
        &slime[1],
        &slime[2],
        &slime[3],
        &slime[4],

    };
    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
       UpdateMusicStream(BGM);
       UpdateMusicStream(knight.GetKnightWalk());
     
        BeginDrawing();
        ClearBackground(WHITE);

        WMapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw the world map
        DrawTextureEx(WorldMap, WMapPos, 0.0, mapScale, WHITE);

        for (auto prop : props)
        {
            prop.Render(knight.getWorldPos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game Oveer", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }
        else // Character is alive case
        {
            std::string knightsHealth = "Health: ";                         // creating a string for player health
            knightsHealth.append(std::to_string(knight.getHealth()), 0, 5); // appending players current health to stringh knights health and reducing amount of digits to 5
            DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);           // Displaying players health value
        }

        knight.tick(GetFrameTime());
        //Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowDimensions[0] > WorldMap.width * mapScale ||
            knight.getWorldPos().y + windowDimensions[1] > WorldMap.height * mapScale)
        {
            knight.undoMovement();
        }

        // Check Prop Collisions
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getCollisionRec(knight.getWorldPos()), knight.getCollisionRec()))
            {
                knight.undoMovement();
            }
        }

        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

             std::string enemysHealth= "Health: ";                         // creating a string for player health
            enemysHealth.append(std::to_string(knight.getHealth()), 0, 5); // appending players current health to stringh knights health and reducing amount of digits to 5
            DrawText(enemysHealth.c_str(), 55.f, 45.f, 40, RED);           // Displaying players health value
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getCollisionRec(), knight.getWeaponCollisionRec()))
                {
                    PlaySound(knight.GetKnightSlash());
                    SetSoundVolume(knight.GetKnightSlash(), 1.0f);
                    enemy->setAlive(false);
                }
            }
        }

        //Stop Drawing
        EndDrawing();
    }
    UnloadMusicStream(BGM);
    UnloadSound(knight.GetKnightSlash());
    UnloadMusicStream(knight.GetKnightWalk());
    UnloadTexture(WorldMap);
    CloseAudioDevice();
    CloseWindow();
}