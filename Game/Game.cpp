#include "Engine.h"
#include "Player.h"

//#include "SDL3/SDL.h"

using namespace nu;

int main()
{
    // INITIALIZATION
    engine.Initialize();

  
    //Mesh mesh{ { Vector2{-3, 3}, Vector2{3, 3}, Vector2{0, 0} }, Color{0.0f, 0.0f, 1.0f} };
    Mesh mesh{ 
        {
        Vector2{3, 0},
        Vector2{5, 0},
        Vector2{5, 1},
        Vector2{3, 1},
        Vector2{4, 2},
        Vector2{7, 2},
        Vector2{7, 4},
        Vector2{4, 4},
        Vector2{3, 5},
        Vector2{5, 5},
        Vector2{5, 6},
        Vector2{3, 6},
        Vector2{1, 4},
        Vector2{0, 4},
        Vector2{1, 3},
        Vector2{0, 2},
        Vector2{1, 2},
        Vector2{3, 0} },
        Color{0.0f, 0.0f, 1.0f}
    };
    Player player{800.0f, Transform{Vector2{640.0f, 512.0f}, 0.0f, 20.0f}, std::vector<Mesh>{ mesh } };

    std::vector<Vector2> points;

    Vector2 position{ 640, 512 };
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
        engine.Update();

        player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime())); //90 degrees per second
        player.Update(engine.GetTime().GetDeltaTime());
        
        if (engine.GetInput().GetButtonPressed(Input::MouseButton::Left)) //paint
        {
            points.push_back(engine.GetInput().GetMousePosition());
        }

        if (engine.GetInput().GetButtonDown(Input::MouseButton::Left)) //paint
        {
            if (points.empty())
            {
                points.push_back(engine.GetInput().GetMousePosition());
            }
            else 
            {
                Vector2 v = points.back() - engine.GetInput().GetMousePosition();
                if (v.Length() > 30.0f)
                {
                points.push_back(engine.GetInput().GetMousePosition());
                }
            }
        }

        if (engine.GetInput().GetButtonPressed(Input::MouseButton::Right)) //paint
        {
            if (!points.empty()) points.pop_back();
        }

        //RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        engine.GetRenderer().Clear();



        for (int i = 0; i < (int)points.size() - 1; ++i) {
            engine.GetRenderer().SetColor((float)255, (float)255, (float)255);
            //renderer.DrawFillRect(points[i].x, points[i].y, 10, 10);
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        //draw a buncha points

        // character
        player.Draw(engine.GetRenderer());
        // TEST CODE END
        
        engine.GetRenderer().Present(); // Render the screen
    }

    // SHUTDOWN
    engine.Shutdown();

    return 0;
}
