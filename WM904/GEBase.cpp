#include <iostream>
#include "GamesEngineeringBase.h" // Include the GamesEngineeringBase 
#include "Colour.h"
#include "Mathf.h"
using namespace std;
using namespace Mathf;

int main() {

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    GamesEngineeringBase::Window canvas;
    canvas.create(1024, 768, "Tiles");
    bool running = true; // Variable to control the main loop's running state.

    Colour::Colour purple = Colour::Colour(128,0,128);

    Vector2 vec2;

    Vector2 randomVec = Vector2(5,5);
    Vector2 randomVec1 = Vector2(4,0);

    cout << randomVec.x << randomVec.y << endl;

    cout << randomVec1.x << randomVec1.y << endl;

    Vector2 sum = randomVec + randomVec1;
    std::cout << sum.x << sum.y << endl;

    Vector2 deducted = randomVec - randomVec1;

    std::cout << deducted.x << "," << deducted.y << endl;

    Vector2 division = randomVec1 / 4;

    std::cout << division.x << "," << division.y << endl;

    while (running)
    {
        // Check for input (key presses or window events)
        if (canvas.keyPressed(VK_ESCAPE)) break;
        
        // Clear the window for the next frame rendering
        canvas.clear();
        // Update game logic

        // Draw();         
        canvas.draw(512, 384, 255, 255, 255);

        Colour::Colour red = Colour::Colour::Red();


        for (int i = 0; i < canvas.getWidth(); i++)
        {
            for (int j = 0; j < canvas.getHeight(); j++)
            {
                canvas.draw(i,j,purple.red,purple.green,purple.blue);

            }
        }

        for (int i = 0; i < canvas.getHeight(); i++)
        {
            canvas.draw(512, i, 255,255,255);
        }
        for (int i = 0; i < canvas.getWidth(); i++)
        {
            canvas.draw(i,canvas.getHeight() * .5f, 255,255,255);
        }

        // Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
        canvas.present();
    }
    return 0;
}