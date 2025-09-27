#include <SFML/Graphics.hpp>
#include <iostream>
#include <mutex>
#include <thread>
#pragma once

using namespace std;
using namespace sf;

class screen
{
private:
    RenderWindow *window = nullptr;
    Image image;
    Texture texture;
    Sprite sprite;
    mutex mtx;               // to protect the data being shared
    thread rendering_thread; // thread to run window
    bool update_image = false;
    bool runing = true;

public:
    bool window_is_open;

private:
    void create_window_loop()
    {
        // make window
        window = new RenderWindow(VideoMode(1000, 1000), "main window");
        image.create(1000, 1000, Color::Black);
        texture.loadFromImage(image);
        sprite.setTexture(texture);

        // start loop
        {
            lock_guard<mutex> lock(mtx);
            window_is_open = true;
        }
        while (window->isOpen() && runing == true)
        {

            // close
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
            {
                lock_guard<mutex> lock(mtx); // lock while drawing
                window->draw(sprite);
            }
            window->display();
        }
        // Ensure window_is_open is false when exiting
        lock_guard<mutex> lock(mtx);
        window_is_open = false;
    }

public:
    screen()

    {
    }

    void add_pixel(int x_position, int y_postion, Color colour = Color::White)
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
    void wait_until_closed()
    {
        while (true)
        {
            lock_guard<mutex> lock(mtx);
            if (window_is_open == false)
            {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
};