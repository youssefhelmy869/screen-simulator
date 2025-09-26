#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace sf;



// fix threading  and sfml contectiomn in thread ownership

class screen
{
private:
    RenderWindow window;
    Image image;
    Texture texture;
    Sprite sprite;
    mutex mtx;            // to protect the data being shared
    thread window_thread; // thread to run window

    void create_window_loop()
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
            window.clear();
            {
                lock_guard<mutex> lock(mtx); // lock while drawing
                window.draw(sprite);
            }
            window.display();
        }
    }

public:
    screen()

        : window(VideoMode(1000, 1000), "main window")
    {
        image.create(1000, 1000, Color::Black);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
    }

    void add_pixsel(int x_position, int y_postion, Color colour = Color::White)
    {

        lock_guard<mutex> lock(mtx);
        image.setPixel(x_position, y_postion, colour);

        texture.update(image);
    }
    void run()
    {
        window_thread = thread(screen::create_window_loop, this);

    }
    ~screen()
    {
        if (window.isOpen())
        {
            window.close();
        }
        if (window_thread.joinable())
        {
            window_thread.join();
        }
    }
};