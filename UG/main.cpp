
#include <SFML\Graphics.hpp>

using namespace std;

int main()
{
    // Create the main rendering window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();
        }

        // Clear the screen (fill it with black color)
        App.Clear();

        // Display window contents on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}
