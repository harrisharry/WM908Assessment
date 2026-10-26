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

    DataStructures::StackInt intStack;

    //Vector3::Dot();

    GraphicsEngine graphics;

    graphics.StartUp();

    intStack.Push(1);
    intStack.Push(5);
    intStack.Push(7);


    //Main loop of the engine / system.
    while (running)
    {
        //Check if the graphics engine has detected that it needs to close.
        if (graphics.ShouldClose()) break;
        graphics.Update();

        intStack.DebugStack();

    }

    std::cout << "Poped value is " << intStack.Pop() << std::endl;
    std::cout << "Poped value is " << intStack.Pop() << std::endl;

    intStack.DebugStack();

    intStack.Push(1000);

    intStack.DebugStack();
    return 0;
}