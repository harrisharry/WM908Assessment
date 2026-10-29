#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase 
#include "Colour.h"
#include "Mathf.h"
#include "GraphicsEngine.h"
#include <filesystem>
#include "Entity.h"

#include "DStructures.h"
using namespace std;
using namespace CustomMath;


int main() {

    DataStructures::List<GameObject*> gameObjects;

    Hero* hero = new Hero();
    gameObjects.Add(hero);
    
    gameObjects.DebugList();

    gameObjects.Remove(hero);
    gameObjects.DebugList();
    gameObjects.Begin();
    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    bool running = true; // Variable to control the main loop's running state.

    GraphicsEngine graphics;

    graphics.StartUp(gameObjects);

    //Main loop of the engine / system.
    while (running)
    {
        //Check if the graphics engine has detected that it needs to close.
        if (graphics.ShouldClose()) break;
        graphics.Update(0.00166);

        for (DataStructures::ListIterator iterator = gameObjects.Begin(); iterator != gameObjects.End();iterator++) {

            
        }


    }
    

    return 0;
}