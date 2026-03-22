#include <vector>
#include <raylib.h>
#include <iostream>
#include "grid.hpp"

#define WIDTH 600
#define HEIGHT 600
const int cellSize = 5;
int main()
{
    
    InitWindow(WIDTH, HEIGHT, "Reaction Diffusion");
    Grid grid(WIDTH, HEIGHT, cellSize);

    while (!WindowShouldClose()){
        for (int i = 0; i < 5; i++)
            grid.update();
        BeginDrawing();
        ClearBackground(BLACK);
        grid.draw();
        EndDrawing();
        
        grid.mouseactions();
    }
    CloseWindow();
    return 0;
}

