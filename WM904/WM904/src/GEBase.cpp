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
using namespace std;
using namespace CustomMath;

enum SpriteIndex {
    HeroSprite
};

int main() {

    DataStructures::List<GameObject*> gameObjects;

    GraphicsEngine graphics;
    graphics.StartUp(gameObjects);


    Hero* hero = new Hero; //Create the object.
    gameObjects.Add(hero); //Add it to the gameobjects list.
    //hero->SetSprite(graphics.GetSpriteAtIndex(HeroSprite)); //Set the sprite of the object using the preloaded ones from the graphics engine.
    hero->SetSprite(graphics.GetSpriteDef(Wizard));

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


        graphics.Update(0.0166);

        for (DataStructures::ListIterator iterator = gameObjects.Begin(); iterator != gameObjects.End(); iterator++) {
            
            iterator->data->Update(0.0016);
        }


    }
    

    return 0;
}