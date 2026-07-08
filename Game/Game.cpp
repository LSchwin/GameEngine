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

    nu::Time time;

    std::vector<Vector2> points;
    Vector2 position{ 640, 512 };


    float speed = 400.0f;

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
        time.Tick();

        // TEST CODE START
        /*
        if (input.GetKeyPressed(SDL_SCANCODE_Q)) std::cout << "pressed\n";
        if (input.GetKeyDown(SDL_SCANCODE_Q)) std::cout << "Down\n";
        if (input.GetKeyReleased(SDL_SCANCODE_Q)) std::cout << "Released\n";

        if (input.GetButtonPressed(Input::MouseButton::Left)) std::cout << "button pwessed\n";
        if (input.GetButtonPressed(Input::MouseButton::Right)) std::cout << "button pwessed\n";
        if (input.GetButtonPressed(Input::MouseButton::Middle)) std::cout << "button pwessed\n";
        */
        
        if (input.GetButtonDown(Input::MouseButton::Left))
        {
            points.push_back(input.GetMousePosition());
        }

        Vector2 velocity{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) velocity.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) velocity.x = speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) velocity.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) velocity.y = speed;
        position += (velocity * time.GetDeltaTime());

        //RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        renderer.Clear();


        for (size_t i = 0; i < points.size(); ++i) {
            renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
            //points[i] = points[i] + vel;
            renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
        }
        //draw a buncha points

        renderer.SetColor(RandomFloat(), RandomFloat(), RandomFloat());
        renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

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

        // TEST CODE END
        
        renderer.Present(); // Render the screen
        
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}
