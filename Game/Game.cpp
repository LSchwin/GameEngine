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

  
    Mesh mesh{ { Vector2{-3, 3}, Vector2{3, 3}, Vector2{0, 0} }, Color{0.0f, 0.0f, 1.0f} };
    Actor player{ Transform{Vector2{640.0f, 512.0f}, 0.0f, 50.0f}, std::vector<Mesh>{ mesh } };

    std::vector<Vector2> points;

    Vector2 position{ 640, 512 };
    float speed = 600.0f;
    Vector2 velocity{ 0.0f, 0.0f };

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
        
        if (input.GetButtonPressed(Input::MouseButton::Left))
        {
            points.push_back(input.GetMousePosition());
        }

        if (input.GetButtonDown(Input::MouseButton::Left))
        {
            if (points.empty())
            {
                points.push_back(input.GetMousePosition());
            }
            else 
            {
                Vector2 v = points.back() - input.GetMousePosition();
                if (v.Length() > 30.0f)
                {
                points.push_back(input.GetMousePosition());
                }
            }
        }

        if (input.GetButtonPressed(Input::MouseButton::Right))
        {
            if (!points.empty()) points.pop_back();
        }

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = speed;
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));

        player.Update(time.GetDeltaTime());

        //velocity += (force * time.GetDeltaTime());
        //position += (velocity * time.GetDeltaTime());
         
        //position.x = Wrap(0.0f, 1920.0f, position.x);
        //position.y = Wrap(0.0f, 1024.0f, position.y);


        //RENDER
        renderer.SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        renderer.Clear();



        for (int i = 0; i < (int)points.size() - 1; ++i) {
            renderer.SetColor((float)255, (float)255, (float)255);
            //renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
            renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        //draw a buncha points

        // character
        player.Draw(renderer);
        //renderer.SetColor(0.0f, 200.0f, 50.0f);
        //renderer.DrawFillRect(position.x - 20, position.y - 20, 40, 40);

        // TEST CODE END
        
        renderer.Present(); // Render the screen
        
    }

    // SHUTDOWN
    renderer.Shutdown();

    return 0;
}
