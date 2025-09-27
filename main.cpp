#include "screen.h"
#include <iostream>

int main()
{
    std::cout<<"creating screen"<<endl;
    screen s;
    s.run();

    // Draw three pixels
    s.add_pixel(100, 100);
    s.add_pixel(200, 200);
    s.add_pixel(300, 300);

    std::cout << "Window is open. Close it to exit..." << std::endl;
    s.wait_until_closed();

    std::cout << "Window closed. Exiting program." << std::endl;
    return 0;
}
