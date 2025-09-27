/// the run() takes the main thread while the rest of the mian that run() was called in will be excuted by a logic_thread

#include <SFML/Graphics.hpp>
#include <thread>
#include <string>
#include <iostream>
#include <mutex>

using namespace std;
using namespace sf;

class screen
{
private:
    RenderWindow *window = nullptr;
    Image image;
    Texture texture;
    Sprite sprite;
    mutex mtx;
    thread logic_thread;
    bool update_image;
    bool runing;

public:
    bool window_is_open;

private:
    void create_window(int x = 800, int y = 800)
    {
        window = new RenderWindow(VideoMode(x, y), "main window");
        image.create(x, y);
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        // start loop

        window_is_open = true;

        while (window->isOpen() && runing == true)
        {
            Event close_event;

            while (window->pollEvent(close_event))
            {
                if (close_event.type == Event::Closed)
                {
                    window->close();
                    lock_guard<mutex> lock(mtx);
                    window_is_open = false;
                }
            }
            if (update_image == true)
            {
                texture.update(image);
                update_image = false;
            }
            window->clear();
            window->draw(sprite);
            window->display();
        }
        window_is_open = false;
    }

public:
    void add_pixel(int x_position, int y_postion, Color colour = Color::White)
    {

        lock_guard<mutex> lock(mtx);
        image.setPixel(x_position, y_postion, colour);
        update_image = true;
    }

    template <typename Func>
    void run(Func rest_of_main)
    {
        
        logic_thread = thread([&, rest_of_main]()
                              { rest_of_main(); });

   
        create_window();

        
        if (logic_thread.joinable())
        {
            logic_thread.join();
        }
    }

    ~screen()
    {
        runing = false;
        if (window && window->isOpen())
            window->close();
        if (logic_thread.joinable())
            logic_thread.join();
    }
};
