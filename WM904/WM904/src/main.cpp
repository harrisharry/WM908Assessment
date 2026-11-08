#pragma once
#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase 
#include "Colour.h"
#include "Mathf.h"
#include "GraphicsEngine.h"
#include <filesystem>
#include "Entity.h"
#include "FileLoader.h"
#include "DStructures.h"
#include "PhysicsEngine.h"
#include "TileManager.h"
#include "ObjectFactory.h"
#include "Timer.h"

using namespace std;
using namespace CustomMath;

enum SpriteIndex {
    HeroSprite
};

int main() {
    unsigned int frames = 0;

    DataStructures::List<GameObject*> gameObjects;

    GraphicsEngine graphics;
    graphics.StartUp(gameObjects);

    PhysicsEngine physics;
    physics.StartUp(gameObjects);


    ObjectFactory* factory = new ObjectFactory(&gameObjects);
    TileManager tileManager(graphics.GetTileDef(),graphics.GetSpriteDef());
    


    Hero* hero = new WizardHero; //Create the object.
    hero->Position(CustomMath::Vector3(1,1,0));
    //Set the sprite of the object using the preloaded ones from the graphics engine.
    hero->SetSprite(graphics.GetSpriteDef(Wizard));

    tileManager.SetHeroRef(hero);
    tileManager.SetFactory(factory);
    tileManager.LoadMap("./Resources/smallMap.txt", gameObjects);


    gameObjects.Add(hero); //Add it to the gameobjects list.

    //Spawner* spawner = new Spawner(CustomMath::Vector3(3,0,0),hero,factory);
    //spawner->SetSprite(graphics.GetSpriteDef(Spawned));
    //spawner->SetSpawnedSprite(graphics.GetSpriteDef(Skeleton_Sword));
    //gameObjects.Add(spawner);

    //Enemy* anotherObject = new Enemy(hero);
    //anotherObject->Position(Vector3(8, 1, 0));
    //SphereCollider* collider1 = new SphereCollider(.5f, Vector3(2, 0, 0));
    //collider1->Move(true);
    //anotherObject->SetCollider(collider1);
    //anotherObject->SetSprite(graphics.GetSpriteDef(Skeleton_Sword));
    //gameObjects.Add(anotherObject);
 

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    bool running = true; // Variable to control the main loop's running state.

    //Loader::LoadFile("./Resources/testText.txt");
    //Main loop of the engine / system.
    Time::Timer fpsTimer;
    Time::Timer deltaTimeTimer;
    float fps = 0;
    fpsTimer.Start();
    while (running)
    {
        deltaTimeTimer.Stop();
        float deltaTime = deltaTimeTimer.Duration() / 1000; //time passed in miliseconds, we want it in seconds.
        std::cout << "Delta is" << deltaTime << std::endl;
        deltaTimeTimer.Start();
        //Check if the graphics engine has detected that it needs to close.
        if (graphics.ShouldClose()) break;

        CustomMath::Vector2 totalInput = CustomMath::Vector2::Zero();
        if (graphics.GetWindow()->keyPressed('W'))
            totalInput += CustomMath::Vector2(0, -1);
        if (graphics.GetWindow()->keyPressed('S'))
            totalInput += CustomMath::Vector2(0, 1);
        if (graphics.GetWindow()->keyPressed('A'))
            totalInput += CustomMath::Vector2(-1, 0);
        if (graphics.GetWindow()->keyPressed('D'))
            totalInput += CustomMath::Vector2(1, 0);
        if (graphics.GetWindow()->mouseButtonPressed(MouseLeft)) {
            //std::cout << "Left mouse clicked.\n";
            int x = graphics.GetWindow()->getMouseX();
            int y = graphics.GetWindow()->getMouseY();

            //Convers to world position by adding the cam pos and - the cam offset.
            CustomMath::Vector2 dir = CustomMath::Vector2(x,y) + graphics.GetCamera()->Position() - graphics.GetCamera()->Offset() - CustomMath::Vector2(hero->Position().x, hero->Position().y);
            GameObject* proj = hero->Attack(dir);
            if (proj != nullptr) {
                proj->SetSprite(graphics.GetSpriteDef(Wizard));
                factory->AddObject(proj);
            }
        }

        hero->SetInputVec(totalInput);

        for (auto it = gameObjects.Begin(); it != gameObjects.End(); it++) {
            it->data->Update(deltaTime); //Update all game objects.
        }
        graphics.GetCamera()->Position(Vector2(hero->Position().x,hero->Position().y));
        physics.Update(deltaTime);
        graphics.Update(deltaTime);

        //newTimer.Stop();
        //std::cout << "Time took is " << newTimer.Duration() << std::endl;
        fpsTimer.Stop();
        frames++;
        double time = fpsTimer.Duration(); 
        if (time >= 500) {
            std::cout << "Frames passed: " << frames << std::endl;
            fps = (frames * 1000) / time;
            frames = 0;
            fpsTimer.Start();
        }
        
    }
    

    return 0;
}