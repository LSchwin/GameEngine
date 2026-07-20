#include "Engine.h"
#include "Player.h"
#include "Enemy.h"

#include <fmod.hpp>

//#include "SDL3/SDL.h"

using namespace nu;

int main()
{
    // INITIALIZATION
    engine.Initialize();


    // create audio system
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    FMOD::Sound* soundTest = nullptr;
    audio->createSound("test.wav", FMOD_DEFAULT, 0, &soundTest);

    std::vector<FMOD::Sound*> sounds;

    FMOD::Sound* sound = nullptr;
    audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    

    audio->playSound(soundTest, 0, false, nullptr);

  
    //Mesh mesh{ { Vector2{-3, 3}, Vector2{3, 3}, Vector2{0, 0} }, Color{0.0f, 0.0f, 1.0f} };
    
    //make each vector a (-3 for each????)
    Mesh mesh{ 
        {
        Vector2{ 4, 0 },
        Vector2{ 0, -1 },
        Vector2{ -1, 0 },
        Vector2{ 0, 1 },
        Vector2{ 4, 0 } 
        },
        Color{ 0.7f, 0.6f, 0.6f }
    };

    Mesh mesh2{
        {
        Vector2{ -1, 1 },
        Vector2{ -2, 1 },
        Vector2{ -3, 3 },
        Vector2{ -1, 2 },
        Vector2{ -1, 1 },
        },
        Color{  0.7f, 0.1f, 0.1f  }
    };

    Mesh mesh3{
        {
        Vector2{ -1, -1 },
        Vector2{ -2, -1 },
        Vector2{ -3, -3 },
        Vector2{ -1, -2 },
        Vector2{ -1, -1 },
        },
        Color{  0.7f, 0.1f, 0.1f  }
    };

    Model model{ std::vector<Mesh>{ mesh, mesh2, mesh3 } };

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = model;
    playerDesc.transform = Transform{ Vector2{640.0f, 512.0f}, 0.0f, 20.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.speed = 800.0f;

    Player* player = new Player{playerDesc};
    scene.AddActor(player);

    /*
    for (int i = 0; i < 20; ++i)
    {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = model;
        enemyDesc.transform = Transform{ Vector2{nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth()), nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth())}, 90.0f, 10.0f };
        enemyDesc.velocity = Vector2{ 0.0f, 0.0f };
        enemyDesc.speed = 800.0f;

        Enemy* enemy = new Enemy{enemyDesc};
        scene.AddActor(enemy);
    }
    */

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
        audio->update(); //required

        float dt = engine.GetTime().GetDeltaTime();
  
        //player.Update(dt);
        //enemy.Update(dt);
        scene.Update(dt);
        
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


        //sound test
        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1))
        {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2))
        {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3))
        {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_4))
        {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_5))
        {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }
        //sound test end


        //RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f); // Set render draw color to black
        engine.GetRenderer().Clear();
        
        for (int i = 0; i < (int)points.size() - 1; ++i) {
            engine.GetRenderer().SetColor((float)255, (float)255, (float)255);
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        scene.Draw(engine.GetRenderer());

        // TEST CODE END

        
        
        engine.GetRenderer().Present(); // Render the screen
    }

    // SHUTDOWN
    engine.Shutdown();

    return 0;
}
