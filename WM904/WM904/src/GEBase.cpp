#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase 
#include "Colour.h"
#include "Mathf.h"
#include "GraphicsEngine.h"
#include <filesystem>
using namespace std;
using namespace CustomMath;


int main() {

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    bool running = true; // Variable to control the main loop's running state.


    Vector3 vec1(1.0f, 1.0f, 1.0f);
    Vector3 vec2(2.0f, 2.0f, 2.0f);


    //Vector3::Dot();

    GraphicsEngine graphics;

    graphics.StartUp();


    //Main loop of the engine / system.
    while (running)
    {
        //Check if the graphics engine has detected that it needs to close.
        if (graphics.ShouldClose()) break;
        graphics.Update();

    }
    return 0;
}