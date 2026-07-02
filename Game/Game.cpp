#include "Engine.h"
#include <iostream>

#include "SDL3/SDL.h"

int main()
{
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024);

    SDL_Event e;
    bool quit = false;

    // Define a rectangle YAYYYYYY yip yip
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        renderer.SetColor(0, 0, 0);
        // Set render draw color to black

        renderer.Clear();
        // Clear the renderer

        
        for (int i = 0; i < 1000; ++i) {
            renderer.SetColor(rand() % 256, rand() % 256, rand() % 256);
            renderer.DrawPoint(rand() % 1280, rand() % 1024);
        }
        //draw a buncha points

        renderer.SetColor(rand() % 256, rand() % 256, rand() % 256, rand() % 256);
        // Set render draw color to green
        renderer.DrawFillRect(40, 40, 50, 50);
        // Render the rectangle
        
        renderer.Present();
        // Render the screen
    }

    renderer.Shutdown();

    return 0;

    //fnEngine();
}
