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
    

    //BoxCollider collider1(1,1,Vector3::Zero());
    //BoxCollider collider2(1, 1, Vector3(1.0f,0.0f,0.0f));

    //SphereCollider sphere1(1, Vector3::Zero());
    //SphereCollider sphere2(1, Vector3(2,0,0));
    //sphere1.CheckCollision(&sphere2);



    //for (int i = 0; i < 11; i++) {
    //    for (int j = 0; j < 2; j++) {
    //        GameObject* tile = new GameObject();
    //        tile->SetSprite(graphics.GetSpriteDef(5));
    //        tile->Position(CustomMath::Vector3(i, j, 0));
    //        gameObjects.Add(tile);
    //    }
    //}

    GameObject* anotherObject = new GameObject();
    anotherObject->Position(Vector3(2,0,0));
    SphereCollider* collider1 = new SphereCollider(1,Vector3(2,0,0));
    anotherObject->SetCollider(collider1);
    anotherObject->SetSprite(graphics.GetSpriteDef(Wizard));
    gameObjects.Add(anotherObject);

    Hero* hero = new Hero; //Create the object.
    hero->Position(CustomMath::Vector3(0,0,0));
    SphereCollider* heroCollider = new SphereCollider(1, Vector3::Zero());
    hero->SetCollider(heroCollider);
    //Set the sprite of the object using the preloaded ones from the graphics engine.
    hero->SetSprite(graphics.GetSpriteDef(Wizard));
    gameObjects.Add(hero); //Add it to the gameobjects list.



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

        hero->SetInputVec(totalInput);

        for (auto it = gameObjects.Begin(); it != gameObjects.End(); it++) {
            it->data->Update(0.0166);
        }
        graphics.GetCamera()->Position(Vector2(hero->Position().x,hero->Position().y));
        physics.Update(0.0166);
        graphics.Update(0.0166);


    }
    

    return 0;
}