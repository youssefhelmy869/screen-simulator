#include "screen2.h"
#include <iostream>

using namespace std;
int main()
{
    screen s(600,600);
    cout<<"added 2 pixsel before runing"<<endl;
    s.add_pixel(100,100);
    
    s.run([&]() {
        cout<<"lamba worked"<<endl;
        s.add_pixel(200,200);












    });    
    return 0;
}
