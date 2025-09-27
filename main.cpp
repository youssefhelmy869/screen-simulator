#include "screen2.h"
#include <iostream>

using namespace std;
int main()
{
    screen s(600,600);
    cout<<"added 2 pixsel before runing"<<endl;
    s.add_pixel(100,100);
    cout<<"writing words before run"<<endl;
    s.write_to_window("hi from before run",300,300);
    
    s.run([&]() {
        cout<<"lamba worked"<<endl;
        s.add_pixel(200,200);
        cout<<"printing words after run"<<endl;
        s.write_to_window("hi form after run()",200,200);
        cout<<"done"<<endl;












    });    
    return 0;
}
