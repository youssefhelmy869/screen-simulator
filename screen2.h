/// the run() takes the main thread while the rest of the mian that run() was called in will be excuted by a logic_thread

#include <SFML/Graphics.hpp>
#include <thread>
#include <string>
#include <iostream>
#include <mutex>
#include <vector>

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
    bool update_image = false;
    bool runing;
    int x;
    int y;
    Font font;

    vector<Text> texts;

public:
    bool window_is_open;

private:
    void create_window()
    {

        // start loop

        window_is_open = true;

        while (window->isOpen() && runing == true)
        {
            window->clear();
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

            window->draw(sprite);

            lock_guard<mutex> lock(mtx);
            for (const auto &t : texts)
            {
                window->draw(t);
            }

            window->display();
        }
        window_is_open = false;
    }

public:
    void write_to_window(string data, int x_pos, int y_pos, int size = 20)
    {
        Text text(data, font, size);
        text.setFont(font);
        text.setFillColor(Color::White);
        text.setPosition(x_pos, y_pos);
        lock_guard<mutex> lock(mtx);
        texts.push_back(text);
    }

    screen(int para_x = 800, int para_y = 800)
    {
        x = para_x;
        y = para_y;
        window = new RenderWindow(VideoMode(x, y), "main window");
        image.create(x, y);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
        {
            cerr << "File not found" << endl;
        }

    }

    void add_pixel(int x_position, int y_postion, Color colour = Color::White)
    {

        cout << "adding pixsel" << endl;
        image.setPixel(x_position, y_postion, colour);
        update_image = true;
    }

    template <typename Func>
    void run(Func rest_of_main)
    {
        cout << "run function called" << endl;
        runing = true;
        cout << "logic thread created" << endl;
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
