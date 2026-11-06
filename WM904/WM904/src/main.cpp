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

using namespace std;
using namespace CustomMath;

enum SpriteIndex {
    HeroSprite
};

int main() {

    DataStructures::List<GameObject*> gameObjects;

    GraphicsEngine graphics;
    graphics.StartUp(gameObjects);

    PhysicsEngine physics;
    physics.StartUp(gameObjects);



    TileManager tileManager(graphics.GetTileDef());
    tileManager.LoadMap("./Resources/smallMap.txt",gameObjects);
    

    Hero* hero = new WizardHero; //Create the object.
    hero->Position(CustomMath::Vector3(1,1,0));
    //Set the sprite of the object using the preloaded ones from the graphics engine.
    hero->SetSprite(graphics.GetSpriteDef(Wizard));
    gameObjects.Add(hero); //Add it to the gameobjects list.

    Enemy* anotherObject = new Enemy(hero);
    anotherObject->Position(Vector3(3, 1, 0));
    SphereCollider* collider1 = new SphereCollider(.5f, Vector3(2, 0, 0));
    collider1->Move(true);
    anotherObject->SetCollider(collider1);
    anotherObject->SetSprite(graphics.GetSpriteDef(Skeleton_Sword));
    gameObjects.Add(anotherObject);
 

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    bool running = true; // Variable to control the main loop's running state.

    //Loader::LoadFile("./Resources/testText.txt");
    //Main loop of the engine / system.
    while (running)
    {
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
            std::cout << "Left mouse clicked.\n";
            int x = graphics.GetWindow()->getMouseX();
            int y = graphics.GetWindow()->getMouseY();

            CustomMath::Vector2 dir = CustomMath::Vector2(x,y) - CustomMath::Vector2(hero->Position().x,hero->Position().y);
            hero->Attack(dir);
        }

        hero->SetInputVec(totalInput);

        for (auto it = gameObjects.Begin(); it != gameObjects.End(); it++) {
            it->data->Update(0.0166); //Update all game objects.
        }
        graphics.GetCamera()->Position(Vector2(hero->Position().x,hero->Position().y));
        physics.Update(0.0166);
        graphics.Update(0.0166);

    }
    

    return 0;
}