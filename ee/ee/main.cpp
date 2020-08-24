
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme:
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//
#include <iostream>
#include "Field.hpp"

using namespace sf;

int main(int argc, char const** argv)
{
    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE), "SFML window");

    
    sf::Music step;
    if (!step.openFromFile("Ваш путь")) {
        return EXIT_FAILURE;
    }

    Field field;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::MouseButtonPressed)
            {
                field.onMouseBtnPressed(event, step);
            }
        }

        window.clear();
        
        field.draw(window);
        
        window.display();
    }

    return EXIT_SUCCESS;
}
