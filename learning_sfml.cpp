#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

using namespace std;
using namespace sf;
void runwindow_1pixsel()
{
    RenderWindow window(VideoMode(800, 600), "my first sfml app");

    Image image;
    image.create(800, 600, Color::Black);

    Texture texture;
    texture.loadFromImage(image);

    Sprite sprite(texture);

    int x = 100, y = 100;
    int x2 = 200, y2 = 200;

    // main loop

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent((event)))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        image.setPixel(x, y, Color::White);
        image.setPixel(x2, y2, Color::White);

        texture.update(image);

        window.clear();
        window.draw(sprite);
        window.display();
    }
}
void runwindow_showtext()
{
    RenderWindow window(VideoMode(800, 600), "CPU I/O Window");

    Font font;

    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        // put a font (like arial.ttf) in the same folder
        return;
    }

    Text text;
    text.setFont(font);
    text.setString("Hello from CPU!");
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(50, 50);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(text); // draw the text
        window.display();
    }
}
int main()
{

    runwindow_showtext();
    return 0;
}
