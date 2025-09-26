#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

void run_window()
{
    RenderWindow window(VideoMode(1000, 1000), "main window");

    // main loop
    while (window.isOpen())
    {
        Event event;

        // check to see if window in closed
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
}
class screen
{
private:
    RenderWindow window;

public:
    screen()

        : window(VideoMode(1000, 1000), "main window")
    {
    }
    void run()
    {
        // start loop
        while (window.isOpen())
        {
            // close
            Event close_event;

            while (window.pollEvent(close_event))
            {
                if (close_event.type == Event::Closed)
                {
                    window.close();
                }
            }
        }
    }
};