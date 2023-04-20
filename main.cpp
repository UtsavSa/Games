// simple1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Game.h"

using namespace sf;





// things need to do here
// create a window
// game class
// game loop
//update and render
//create shapes
//move shapes
//positions
//getting mouse positions and inputs
//gfetting keyboard inputs
//removing shapes






int main()
{


    // loading in the window

  //  RenderWindow window(VideoMode(1600, 900), "First Game", Style::Titlebar | Style::Close);
  //  Event ev;  // capturing what key has been pressed 
                // especially after window has appeared (line before this)


   // sf::RenderWindow window(sf::VideoMode(640, 460), "First Game", sf::Style::Titlebar | sf::Style::Close);
    //sf::Event ev;


    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));


    //Init Game engiene

    Game game;

    // Game Loop

    while (game.running() && !game.getEndGame())
    {
        //Event polling (dectecting what key or mouse button has been pressed while the game is on



        /*
        while (window.pollEvent(ev)) // save whatever is input (keyboard or mouse) into ev.
        {
            switch (ev.type) // what type of input is it
            {

            case Event::Closed:
                window.close();
                break;
            case Event::KeyPressed:
                if (ev.key.code == Keyboard::Escape)
                    window.close();
                break;
                //if (ev.key.code == Keyboard::Enter)
                 //   window.close();
              //  break;

            }


        } 
        */
       
        //Update

        game.update();
        game.render();

       
        // Render
        //window.clear(Color(167, 0, 150, 0)); // clear old frame

        // draw the game
        //window.display();  // tell app window is done drawing
        
    
    }// while loop close, end of application

    return 0;


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
