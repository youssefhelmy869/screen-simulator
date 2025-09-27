#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace sf;


class screen
{
private:
    RenderWindow *window = nullptr;
    Image image;
    Texture texture;
    Sprite sprite;
    mutex mtx;            // to protect the data being shared
    thread rendering_thread; // thread to run window
    bool update_image = false;
    bool runing = true;

    void create_window_loop()
    {
        // make window
        window = new RenderWindow(VideoMode(1000, 1000), "main window");
        image.create(1000, 1000, Color::Black);
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        // start loop
        while (window->isOpen() && runing == true)
        {

            // close
            Event close_event;

            while (window->pollEvent(close_event))
            {
                if (close_event.type == Event::Closed)
                {
                    window->close();
                }
            }
            if (update_image == true)
            {
                texture.update(image);
                update_image = false;
            }
            window->clear();
            {
                lock_guard<mutex> lock(mtx); // lock while drawing
                window->draw(sprite);
            }
            window->display();
        }
    }

public:
    screen()

    {
    }

    void add_pixsel(int x_position, int y_postion, Color colour = Color::White)
    {

        lock_guard<mutex> lock(mtx);
        image.setPixel(x_position, y_postion, colour);
        update_image = true;
    }
    void run()
    {
        rendering_thread = thread(screen::create_window_loop, this);
    }
    ~screen()
    {
        runing = false;

        if (window && window->isOpen())
        {
            window->close();
        }
        if (window && rendering_thread.joinable())
        {
            rendering_thread.join();
        }

    }
};