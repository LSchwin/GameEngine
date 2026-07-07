#include "Engine.h"


//#include "SDL3/SDL.h"

using namespace nu;

int main()
{
    // INITIALIZATION
    nu::Renderer renderer;
    renderer.Initialize("Game Engine", 1920, 1024); //prof did 1280 instead of 1920

    nu::Input input;
    input.Initialize();

    //std::cout << sizeof(Vector2) << std::endl;

    Vector2 vel{ 0.5f, 0.0f };

    std::vector<Vector2> v;
    for (int i = 0; i < 300; ++i)
    {
        Vector2 vec{ RandomFloat(1920) , RandomFloat(1024) };
        v.push_back(vec);
    }

    


    // MAIN LOOP
    bool quit = false;
    while (!quit) {
        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        input.Update();

        if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "Down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "Released\n";

        //RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        renderer.Clear();


        for (size_t i = 0; i < v.size(); ++i) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            v[i] = v[i] + vel;
            renderer.DrawPoint((float)RandomInt(1920), (float)RandomInt(1024));
        }
        //draw a buncha points

        renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        

        renderer.DrawFillRect(input.GetMousePosition().x - 20, input.GetMousePosition().y - 20, 40, 40);

        /*for (int i = 0; i < 20; ++i) {
            float xRand = (float)RandomInt(1910);
            float yRand = (float)RandomInt(1014);
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            renderer.DrawFillRect(xRand, yRand, xRand + 10, yRand + 10);
        }*/
        // Render the rectangles

        /*for (int i = 0; i < 20; ++i) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            renderer.DrawLine((float)RandomInt(1920), (float)RandomInt(1024), (float)RandomInt(1920), (float)RandomInt(1024));
        }*/
        // Render the lines
        
        renderer.Present();
        // Render the screen
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}
