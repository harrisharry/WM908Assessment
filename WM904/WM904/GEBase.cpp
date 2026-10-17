#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase 
#include "Colour.h"
#include "Mathf.h"
#include "GraphicsEngine.h"
using namespace std;
using namespace Mathf;


int main() {

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    bool running = true; // Variable to control the main loop's running state.
    
    Image testImage;


    testImage.load("C:/Users/u5843352/Github/WM908Assessment/WM904/TestSprite.png");
    if (testImage.data == NULL) {
        cout << "Image data is null.\n";
    }


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