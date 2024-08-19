#include "raylib.h"
int main()

{
    // Window Dimenstions
    int width = 600;
    int height = 500;
    //Circle placement
    int centerX = width/2;
    int centerY = height/2;
    //circle edges
    int circle_radius = 25;
    int l_circle_x{ centerX - circle_radius};
    int r_circle_x{ centerX + circle_radius};
    int u_circle_y{ centerY - circle_radius};
    int b_circle_y{ centerY + circle_radius};

    // Axe coordinates
    int Axe_x = 300;
    int Axe_y = 0;
    int Axe_length = 50;

    // Axe Edges
    int l_axe_x{Axe_x};
    int r_axe_x{Axe_x + Axe_length};
    int u_axe_y{Axe_y};
    int b_axe_y{Axe_y + Axe_length};

    // Collision check
    bool collision_with_axe = (b_axe_y >= u_circle_y && 
                              u_axe_y <= b_circle_y  && 
                              l_axe_x <= r_circle_x && 
                              r_axe_x >= l_circle_x);

    int direction = 10;

    InitWindow(width, height, "jOSH'S wINDOW");

    SetTargetFPS(60);
    while(WindowShouldClose() == false)
     {
        BeginDrawing();
        ClearBackground(BLACK);

    
      
        if(collision_with_axe == true)
        {
            DrawText("Game Over!", 400, 200, 20, RED);
        }

       else {
           // update the edges
           l_circle_x = centerX - circle_radius;
           r_circle_x = centerX + circle_radius;
           u_circle_y = centerY - circle_radius;
           b_circle_y = centerY + circle_radius;

           l_axe_x = Axe_x;
           r_axe_x = Axe_x + Axe_length;
           u_axe_y = Axe_y;
           b_axe_y = Axe_y + Axe_length;
           // update collision with axe
           collision_with_axe = (b_axe_y >= u_circle_y && 
                              u_axe_y <= b_circle_y  && 
                              l_axe_x <= r_circle_x && 
                              r_axe_x >= l_circle_x);

                DrawCircle(centerX, centerY, circle_radius, BLUE);
                DrawRectangle(Axe_x, Axe_y, 50, 50, RED);

                Axe_y += direction;
                if (Axe_y >  height || Axe_y < 0)
                {
                    direction = -direction;
                }

                if (IsKeyDown(KEY_D) && centerX < width)
                {
                    centerX += 10;
                }
                if (IsKeyDown(KEY_A) && centerX > 0 )
                {
                    centerX -= 10;
                }
                if (IsKeyDown(KEY_W) && centerY > 0)
                {
                    centerY -= 10;
                }
                if (IsKeyDown(KEY_S) && centerY < height)
                {
                    centerY += 10;
                }
                
        
       }
       EndDrawing();
        
     
    }


    

}