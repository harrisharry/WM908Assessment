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


    //Vector3::Dot();

    //DataStructures::Queue<int> data;
    DataStructures::Stack<int> stack;
    stack.Push(5);
    stack.Push(10);
    stack.Push(3);
    stack.DebugStack();

    stack.Pop();

    stack.DebugStack();

    GraphicsEngine graphics;

    graphics.StartUp();
 
    //data.Enqueue(1);
    //data.Enqueue(4);
    //data.Enqueue(8);

    //data.DebugQueue();

    //data.Dequeue();

    //data.DebugQueue();

    //data.Enqueue(40);

    //data.DebugQueue();

    //Main loop of the engine / system.
    while (running)
    {
        //Check if the graphics engine has detected that it needs to close.
        if (graphics.ShouldClose()) break;

        graphics.Update();


    }


    return 0;
}