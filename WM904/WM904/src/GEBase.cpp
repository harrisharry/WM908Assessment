#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase 
#include "Colour.h"
#include "Mathf.h"
#include "GraphicsEngine.h"
#include <filesystem>

#include "DStructures.h"
using namespace std;
using namespace CustomMath;


int main() {

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    bool running = true; // Variable to control the main loop's running state.

    DataStructures::List<std::string> listData;
    listData.Add("Hello");
    listData.Add("My");
    listData.Add("Name");
    listData.Add("Is");

    listData.DebugList();

    GraphicsEngine graphics;

    graphics.StartUp();

    listData.Remove("My");
    listData.DebugList();

    //Main loop of the engine / system.
    while (running)
    {
        //Check if the graphics engine has detected that it needs to close.
        if (graphics.ShouldClose()) break;

        graphics.Update();


    }


    return 0;
}